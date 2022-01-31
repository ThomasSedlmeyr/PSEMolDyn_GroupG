#ifndef PSEMOLDYN_GROUPG_ANALYZER_H
#define PSEMOLDYN_GROUPG_ANALYZER_H


#include <vector>
#include "SimulationLogic/Particle.h"
#include "ParticleContainers/ParticleContainer.h"
#include "OutputWriter/Writer.h"
#include "OutputWriter/CSVWriter.h"
#include <string>

class Analyzer {
protected:
    /**
     * @brief the particleContainer on which the analysis is carried out
     */
    ParticleContainer* particleContainer;

    /**
     * @brief the particles which should be analyzed
     */
    std::vector<Particle> particles;

    /**
     * @brief filters the particles which should be analyzed
     */
    void getSimulationParticles();

    /**
     * @brief the path to the csvFile in which the results of the analysis will be stored
     */
    std::string pathToCSVfile;

    /**
     * @brief creates the header of the csv-file where the results of the analysis will be stored
     * @return the header of the csv-file
     */
    virtual std::string createHeaderLine() = 0;

    /**
     * @brief the CSV-Writer is used to write the information to a CSV-file
     */
    CSVWriter *writer;

public:
    /**
     * @brief the constructor
     * @param particleContainer the particle container on which the analysis will be carried out
     */
    Analyzer(ParticleContainer *particleContainer);

    /**
     * @brief the analysis is carried out and the result is converted to a string
     * @return the string of the analysis result
     */
    virtual std::string calculationResultsToString() = 0;

    /**
     * @brief carries out the simulation analysis and appends the result to an existing csv-file
     */
    void appendLineToCSVFile();

    /**
     * @brief writes the header of the csv-file
     */
    void writeHeaderLineToCSVFile();

    virtual ~Analyzer();

    /**
     * @brief Sets the ParticleContainer which will be analysed
     * @param particleContainer_new
     */
    void setParticleContainer(ParticleContainer* particleContainer_new);

};
#endif //PSEMOLDYN_GROUPG_ANALYZER_H
