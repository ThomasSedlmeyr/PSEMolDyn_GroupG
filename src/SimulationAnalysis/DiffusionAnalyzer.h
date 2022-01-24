//
// Created by thomas on 18.01.22.
//

#ifndef PSEMOLDYN_GROUPG_DIFFUSIONANALYZER_H
#define PSEMOLDYN_GROUPG_DIFFUSIONANALYZER_H


#include <vector>
#include <array>
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include "SimulationAnalysis/Analyzer.h"

class DiffusionAnalyzer : public Analyzer{
private:
    double diffusion;
    std::vector<std::array<double, 3>> oldPositions;
    void initializeOldPositions();
    std::string calculationResultsToString() override;
    std::string createHeaderLine();

public:
    void calculateDiffusion();

    ~DiffusionAnalyzer() override;

    explicit DiffusionAnalyzer(ParticleContainer *particleContainer);

    double getDiffusion() const;
};


#endif //PSEMOLDYN_GROUPG_DIFFUSIONANALYZER_H
