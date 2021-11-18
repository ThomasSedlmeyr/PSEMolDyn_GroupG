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

private:
    /**
     * reads the specific arguments for every simulation from file
     * @param filename
     */
    bool readParamsAndValues(const std::string &filename);

    /**
    * @brief update the position of all particles
    * @param delta_t timestep to use for calculation
    */
    void calculateX(const double &delta_t);

    /**
    * @brief update the velocity for all particles
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


protected:
    /**
     *@brief names of the expected parameters
     */
    std::vector<std::string> paramNames;

    /**
     * the particleContainer containing all particles used for the simulation process
     */
    ParticleContainer particleContainer;

    /**
     *@brief The argumentContainer used to parse the arguments
     */
    ArgumentContainer argumentContainer;

    /**
     *@brief the number of particles used for the simulation process
     */
    int numberParticles;

    /**
    * @brief Reads the particles from a txt-file into particleContainer
    * @param filename the name of the txt-file were the particles are stored
    */
    virtual bool readParticles(const std::string &filename) = 0;

    /**
     * @brief sets the paramNames to the specific parameters of the simulation
     */
    virtual void initializeParamNames() = 0;

    /**
     * @brief initializes the parameters for the specific simulation with the
     * given values from the particle container
     */
    virtual void setParamsWithValues() = 0;

    /**
     * @brief calculates the force between the two given particles
     * @param p1 particle 1
     * @param p2 particle 2
     * @return force between p1 and p2
     */
    virtual std::array<double, 3> calculateFBetweenPair(Particle &p1, Particle &p2) = 0;

    /**
     * @brief faster but not so nice implementation of force calculation
     */
    virtual void calculateFFast() = 0;

public:
    static const int GRAVITATION = 1;
    static const int LENNARDJONES = 2;
    Simulation();
    virtual~Simulation();

    /**
     * @brief Calculates the new position, the new force and the new velocity for one time step
     * @param delta_t the difference between two time steps
     */
    void calculateOneTimeStep(const double &delta_t);

    /**
     * @brief Performs the whole simulation process
     * @param endTime duration of the simulation
     * @param delta_t the timespan between two simulation time steps
     * @param writer is used to output the simulation results
     * @param numberSkippedPrintedIterations number of not printed time steps
     * @param parametersFileName path to the file containing all required parameters
     * @param particlesFileName path to the file containing information for every particle
     * @param outputFileName name of the output file
     */
    void simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedPrintedIterations,
                  const std::string &parametersFileName, const std::string &particlesFileName,
                  const std::string &outputFileName);
};


#endif //PSEMOLDYN_GROUPG_SIMULATION_H
