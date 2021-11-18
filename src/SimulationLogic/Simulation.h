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
    /**
     *@brief the expected parameters
     */
    std::vector<std::string> paramNames;

    /**
     * the particleContainer containing the particles which were used for the simulation process
     */
    ParticleContainer particleContainer;

    /**
     *@brief The argumentContainer which is used to parse the arguments
     */
    ArgumentContainer argumentContainer;

    /**
     *@brief the number of particles which were used for the simulation process
     */
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

    /**
     * @brief initializes the specific parameters for the simulation with the
     * given values from the particle container
     */
    virtual void setParamsWithValues() = 0;

    /**
     * @brief sets the paramNames to the specific parameters of the simulation
     */
    virtual void initializeParamNames() = 0;

    /**
     * @brief the actual implementation of force calculation between p1 and p2, has to be
     * implemented by every sub-class
     * @param p1 particle 1
     * @param p2 particle 2
     * @return force between p1 and p2
     */
    virtual std::array<double, 3> calculateFBetweenPair(Particle &p1, Particle &p2) = 0;

public:
    static const int GRAVITATION = 1;
    static const int LENNARDJONES = 2;
    Simulation();
    virtual~Simulation();

    /**
     * @brief Calculates the new position, the new force and the new velocity one time step
     * @param delta_t the difference between two time steps
     */
    void calculateOneTimeStep(const double &delta_t);

    /**
     * @Performs the whole simulation process
     *
     * @param endTime duration of the simulation
     * @param delta_t the timespan between two simulation time steps
     * @param writer is used to write the simulation results
     * @param numberSkippedPrintedIterations gives the number of not printed time steps
     * @param parametersFileName the path to the file containing all required parameters
     * @param particlesFileName the path to the file containing information for every particle
     * @param outputFileName the name of the output file
     */
    void simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedPrintedIterations,
                  const std::string &parametersFileName, const std::string &particlesFileName,
                  const std::string &outputFileName);
};


#endif //PSEMOLDYN_GROUPG_SIMULATION_H
