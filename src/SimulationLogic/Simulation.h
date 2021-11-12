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
     * reads the specific arguments for every simulation from file
     * @param filename
     */
    void readParamsAndValues(const std::string &filename);

protected:
    virtual void calculateF() = 0;

    /**
    * @brief Reads the particles from a txt-file into the simulation process
    * @param filename the name of the txt-file were the particles were saved
    */
    virtual void readParticles(const std::string &filename) = 0;
    virtual void setParamsWithValues() = 0;
    virtual void initializeParamNames() = 0;


public:
    Simulation();
    virtual~Simulation();

    const ParticleContainer getParticleContainer() const;
    void calculateOneTimeStep(const double &delta_t);

    void simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedIterations,
                  const std::string &parametersFileName, const std::string &particlesFileName,
                  const std::string &outPutFileName);
};


#endif //PSEMOLDYN_GROUPG_SIMULATION_H
