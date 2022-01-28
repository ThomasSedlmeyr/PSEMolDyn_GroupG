//
// Created by thomas on 04.01.22.
//

#ifndef PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H
#define PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H


#include <array>
#include "Bin.h"
#include "XML_Parser/XMLParser.h"
#include "ParticleContainers/ParticleContainer.h"
#include "Analyzer.h"

class SimulationAnalyzer : public Analyzer{

private:

    /**
     * @brief bins of domain
     */
    std::vector<Bin*> bins;

    /**
     * @brief width of individual bins
     */
    double binWidth;

public:
    /**
     * @brief calculate velocity and density profile
     */
    void calculateVelocityAndDensityProfile();

    /**
     * @brief write in output file
     * @param timeStep used as timestamp
     */
    //bool appendLineToCSVfile(int timeStep);

    /**
     * @brief create or reset CSV file
     * @return returns whether it worked
     */
    //bool createCSV();

    explicit SimulationAnalyzer(ParticleContainer *particleContainer);

    ~SimulationAnalyzer() override;

    std::string calculationResultsToString() override;

    std::string createHeaderLine();
};


#endif //PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H
