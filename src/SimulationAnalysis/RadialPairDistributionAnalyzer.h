//
// Created by thomas on 20.01.22.
//

#ifndef PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONANALYZER_H
#define PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONANALYZER_H


#include <vector>
#include "SimulationAnalysis/Analyzer.h"

class RadialPairDistributionAnalyzer : public Analyzer{
private:
    double startOfIntervall;
    double stepSize;
    int timeStepSize;
    int startTime;
    int currentTime = 0;
public:
    RadialPairDistributionAnalyzer(ParticleContainer *particleContainer,
                                   double startOfIntervall, double stepSize,
                                   int numberOfValues, int startTime, int timeStepSize);

private:
    int numberOfValues;
    std::vector<int> numberParticlesInIntervall;
    std::vector<double> localDensities;

    std::string calculationResultsToString() override;
public:
    void calculateLocalDensities();

    ~RadialPairDistributionAnalyzer() override;

    const std::vector<double> &getLocalDensities() const;

    const std::vector<int> &getNumberParticlesInIntervall() const;

    std::string createHeaderLine() override;
};


#endif //PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONANALYZER_H
