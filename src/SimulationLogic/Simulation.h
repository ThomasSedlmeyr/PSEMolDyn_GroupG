//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_SIMULATION_H
#define PSEMOLDYN_GROUPG_SIMULATION_H

#include <outputWriter/Writer.h>
#include "ParticleContainerDirectSum.h"
#include "Particle.h"
#include "ParticleContainerLinkedCells.h"
#include <vector>
#include <string>
#include <InputReader/ArgumentContainer.h>
#include <Visitors/PosCalculationVisitor.h>
#include <Visitors/VelCalculationVisitor.h>

class Simulation {

private:
    /**
     * reads the specific arguments for every simulation from file
     * @param filename
     */
    bool readParamsAndValues(const std::string &filename);
    /**
     * @brief Calculates the new position, the new force and the new velocity for one time step
     */
    void calculateOneTimeStep();

    /**
     * calculates the force depending on the type of simulation
     */
    virtual void calculateF() = 0;

protected:
    /**
     *@brief names of the expected parameters
     */
    std::vector<std::string> paramNames;

    /**
     * the particleContainer containing all particles used for the simulation process
     */
    ParticleContainer *particleContainer;
    /**
     * @brief Implementation of the position calculation
     */
    PosCalculationVisitor posCalcVisitor;

    /**
     * @brief Implementation of the velocity calculation
     */
    VelCalculationVisitor velCalcVisitor;

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

public:
    static const int GRAVITATION = 1;
    static const int LENNARDJONES = 2;

    virtual~Simulation();

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
