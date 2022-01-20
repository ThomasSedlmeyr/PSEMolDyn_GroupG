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
    RadialPairDistributionCalculator(double startOfIntervall, double stepSize, double numberOfValues);

private:
    double numberOfValues;
    std::vector<int> numberParticlesInIntervall;
    std::vector<double> localDensities;

    void calculationResultsToString() override;
public:
    void calculateLocalDensities();

    ~RadialPairDistributionCalculator() override;

};


#endif //PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONCALCULATOR_H
