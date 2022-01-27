//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_SIMULATION_H
#define PSEMOLDYN_GROUPG_SIMULATION_H

#include <OutputWriter/Writer.h>
#include "ParticleContainers/ParticleContainerDirectSum.h"
#include "Particle.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include "Thermostat.h"
#include <vector>
#include <string>
#include <Visitors/PosCalculationVisitor.h>
#include <Visitors/VelCalculationVisitor.h>

class Simulation {

private:
    /**
     * @brief Calculates the new position, the new force and the new velocity for one time step
     */
    void calculateOneTimeStep(double currentTime);

    /**
     * @brief calculates the force depending on the type of simulation
     */
    virtual void calculateF() = 0;

protected:
    /**
     * @brief the particleContainer containing all particles used for the simulation process
     */
    ParticleContainer *particleContainer;

    Thermostat thermostat;

    const double tInit = XMLParser::T_init_p;

    const int dimensions = XMLParser::dimensionType_p;

    /**
     * @brief Implementation of the position calculation
     */
    PosCalculationVisitor posCalcVisitor;

    /**
     * @brief Implementation of the velocity calculation
     */
    VelCalculationVisitor velCalcVisitor;

    /**
     *@brief the number of particles used for the simulation process
     */
    int numberParticles;

    /**
    * @brief Reads the particles from a xml file into particleContainer
    * @param filename the name of the xml-file were the particles are stored
    */
    virtual bool readParticles(const std::string &filename) = 0;

public:
    static const int GRAVITATION = 1;
    static const int LENNARDJONES = 2;
    static const int SMOOTHEDLENNARDJONES = 3;

    static const int NOTPARALLEL = 0;
    static const int FIRSTPARALLEL = 1;
    static const int SECONDPARALLEL = 2;

    static int numberOfTimeStepsWithFZUp;
    virtual~Simulation();

    /**
     * @brief Calls the simulation process
     * @param endTime duration of the simulation
     * @param delta_t the timespan between two simulation time steps
     * @param writer is used to output the simulation results
     * @param numberSkippedPrintedIterations number of not printed time steps
     * @param parametersFileName path to the file containing all required parameters
     * @param particlesFileName path to the file containing information for every particle
     * @param outputFileName name of the output file
     */
    void
    simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedPrintedIterations, const std::string &inputFile, const std::string &outputFileName, ParticleContainer *particleContainer);

    /**
     * @brief Same as above but with only two parameters, rest is read from XMLParser
     * @param writer is used to output the simulation results
     */
    void simulate(Writer &writer, ParticleContainer *partContainer);

    /**
     * @brief Actual Simulation process
     * @param endTime
     * @param delta_t
     * @param writer
     * @param numberSkippedPrintedIterations
     * @param inputFile
     * @param outputFileName
     * @param partContainer
     */
    void
    simulateLogic(const double &endTime, const double &delta_t, Writer &writer,
                  const int &numberSkippedPrintedIterations,
                  const std::string &inputFile, const std::string &outputFileName, ParticleContainer *partContainer);

    void setupThermostat();
};


#endif //PSEMOLDYN_GROUPG_SIMULATION_H
