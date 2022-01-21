//
// Created by thomas on 20.01.22.
//

#ifndef PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONCALCULATOR_H
#define PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONCALCULATOR_H


#include <vector>
#include "Calculator.h"

class RadialPairDistributionCalculator : public Calculator{
private:
    double startOfIntervall;
    double stepSize;
public:
    RadialPairDistributionCalculator(ParticleContainer *particleContainer,
                                     double startOfIntervall, double stepSize,
                                     int numberOfValues);

private:
    int numberOfValues;
    std::vector<int> numberParticlesInIntervall;
    std::vector<double> localDensities;

    void calculationResultsToString() override;
public:
    void calculateLocalDensities();

    ~RadialPairDistributionCalculator() override;

    const std::vector<double> &getLocalDensities() const;

    const std::vector<int> &getNumberParticlesInIntervall() const;

};


#endif //PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONCALCULATOR_H
