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
    /**
     * @brief the diffusion which is calculated
     */
    double diffusion;

    /**
     * @brief the positions of the particles of the previous time step
     */
    std::vector<std::array<double, 3>> oldPositions;

    /**
     * @brief Sets the OldPositions to the current positions. This function is invoked
     * in the Constructor
     */
    void initializeOldPositions();

    std::string calculationResultsToString() override;
    std::string createHeaderLine();

public:
    /**
     * @brief Calculates the diffusion between two timeSteps
     */
    void calculateDiffusion();

    ~DiffusionAnalyzer() override;

    explicit DiffusionAnalyzer(ParticleContainer *particleContainer);

    double getDiffusion() const;
};


#endif //PSEMOLDYN_GROUPG_DIFFUSIONANALYZER_H
