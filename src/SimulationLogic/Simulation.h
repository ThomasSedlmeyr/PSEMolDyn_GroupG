//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_SIMULATION_H
#define PSEMOLDYN_GROUPG_SIMULATION_H


#include <outputWriter/Writer.h>
#include "ParticleContainer.h"
#include "Particle.h"
#include <vector>
#include <string>
#include <InputReader/ArgumentContainer.h>

class Simulation {


protected:
    std::vector<std::string> paramNames;
    ParticleContainer particleContainer;
    ArgumentContainer argumentContainer;
    int numberParticles;

private:
    /**
    * @brief calculate the position for all particles
    * @param delta_t timestep to use for calculation
    */
    void calculateX(const double &delta_t);

    /**
    * @brief calculate the velocity for all particles
    * @param delta_t timestep to use for calculation
    */
    void calculateV(const double &delta_t);

    /**
     * @brief a function to pass to applyFToParticlePairs in calculateF() and call the actual force calculation implementation
     * @param p1, p2 particle pair for force calculation
     */
    std::function<std::array<double, 3> (Particle&,Particle&)> callForceCalculation = [=](Particle &p1, Particle &p2) {
        return this->calculateFBetweenPair(p1, p2);
    };

    /**
     * reads the specific arguments for every simulation from file
     * @param filename
     */
    bool readParamsAndValues(const std::string &filename);


protected:

    /**
    * @brief Reads the particles from a txt-file into the simulation process
    * @param filename the name of the txt-file were the particles were saved
    */
    virtual bool readParticles(const std::string &filename) = 0;
    virtual void setParamsWithValues() = 0;
    virtual void initializeParamNames() = 0;

    /**
     * @brief the actual implementation of force calculation between p1 and p2, has to be implemented by every sub-class
     * @param p1 particle 1
     * @param p2 particle 2
     * @return force between p1 and p2
     */
    virtual std::array<double, 3> calculateFBetweenPair(Particle &p1, Particle &p2) = 0;

public:
    static const int GRAVITATION = 0;
    static const int LENNARDJONES = 1;
    Simulation();
    virtual~Simulation();

    const ParticleContainer getParticleContainer() const;
    void calculateOneTimeStep(const double &delta_t);

    void simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedIterations,
                  const std::string &parametersFileName, const std::string &particlesFileName,
                  const std::string &outPutFileName);
};


#endif //PSEMOLDYN_GROUPG_SIMULATION_H
