//
// Created by thomas on 18.01.22.
//

#ifndef PSEMOLDYN_GROUPG_DIFFUSIONCALCULATOR_H
#define PSEMOLDYN_GROUPG_DIFFUSIONCALCULATOR_H


#include <vector>
#include <array>
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include "Calculator.h"

class DiffusionCalculator : public Calculator{
private:
    std::vector<std::array<double, 3>> oldPositions;
    void initializeOldPositions();
    void calculationResultsToString() override;

public:
    void calculateDiffusion();

    ~DiffusionCalculator() override;

    DiffusionCalculator();


};


#endif //PSEMOLDYN_GROUPG_DIFFUSIONCALCULATOR_H
