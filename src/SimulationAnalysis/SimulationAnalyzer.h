//
// Created by thomas on 04.01.22.
//

#ifndef PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H
#define PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H


#include <array>
#include "Bin.h"
#include "XML_Parser/XMLParser.h"
#include "ParticleContainers/ParticleContainer.h"

class SimulationAnalyzer {

private:
    /**
     * @brief bins of domain
     */
    std::vector<Bin*> bins;

public:
    /**
     * @brief calculate velocity and density profile
     */
    void calculateVelocityAndDensityProfile(ParticleContainer *particleContainer);

    /**
     * @brief write in output file
     * @param timeStep used as timestamp
     */
    bool appendLineToCSVfile(int timeStep);

    /**
     * @brief create or reset CSV file
     * @return returns whether it worked
     */
    bool createCSV();
};


#endif //PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H
