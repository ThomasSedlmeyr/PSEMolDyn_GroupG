//
// Created by thomas on 04.01.22.
//

#ifndef PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H
#define PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H


#include <array>
#include "Bin.h"

class SimulationAnalyzer {

private:
    std::array<Bin, 50> bins;
    void calculateVelocityAndDensityProfile();

public:
    void appendLineToCSVfile(int timeStep);
};


#endif //PSEMOLDYN_GROUPG_SIMULATIONANALYZER_H
