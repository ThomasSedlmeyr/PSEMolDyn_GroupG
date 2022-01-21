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
    double diffusion;
    std::vector<std::array<double, 3>> oldPositions;
    void initializeOldPositions();
    void calculationResultsToString() override;

public:
    void calculateDiffusion();

    ~DiffusionCalculator() override;

    explicit DiffusionCalculator(ParticleContainer *particleContainer);

    double getDiffusion() const;
};


#endif //PSEMOLDYN_GROUPG_DIFFUSIONCALCULATOR_H
