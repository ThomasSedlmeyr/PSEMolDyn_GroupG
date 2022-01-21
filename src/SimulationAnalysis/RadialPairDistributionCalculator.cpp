#include "RadialPairDistributionCalculator.h"
#include "utils/ArrayUtils.h"
#include <math.h>

RadialPairDistributionCalculator::RadialPairDistributionCalculator(ParticleContainer *particleContainer,
                                                                   double startOfIntervall, double stepSize,
                                                                   int numberOfValues) : Calculator(
        particleContainer), startOfIntervall(
        startOfIntervall), stepSize(stepSize), numberOfValues(numberOfValues) {

    double currentValue = startOfIntervall;
    numberParticlesInIntervall = std::vector<int>(numberOfValues);
    localDensities = std::vector<double>(numberOfValues);
}

void RadialPairDistributionCalculator::calculateLocalDensities() {
    double difference = 0;
    int index = 0;
    for (auto it = particles.begin(); it != particles.end(); it++) {
        for (auto it2 = it + 1; it2 != particles.end(); it2++) {
            Particle p1 = *it;
            Particle p2 = *it2;
            double distance = 0;
            if(!(p1 == p2)){
                difference = p1.getX()[0] - p2.getX()[0];
                distance = difference * difference;
                difference = p1.getX()[1] - p2.getX()[1];
                distance += difference * difference;
                difference = p1.getX()[2] - p2.getX()[2];
                distance += difference * difference;
            }
            distance = sqrt(distance);
            index = ((int) (distance - startOfIntervall) / stepSize) - 1;

            //We have to check if the index is in our intervall
            if(index < numberParticlesInIntervall.size()){
                //We increment the correct particle counter
                numberParticlesInIntervall[index]++;
            }
        }
    }
    //calculation of the local densities
    double ri, riPlusStepSize, riCubic, riPlusStepSizeCubic;
    for(int i = 0; i < localDensities.size(); i++){
        ri = startOfIntervall + i * stepSize;
        riPlusStepSize = ri + stepSize;
        riCubic = ri * ri * ri;
        riPlusStepSizeCubic = riPlusStepSize * riPlusStepSize * riPlusStepSize;
        localDensities[i] = numberParticlesInIntervall[i] / ((4.0/3)*M_PI*(riPlusStepSizeCubic - riCubic));
    }
}

const std::vector<int> &RadialPairDistributionCalculator::getNumberParticlesInIntervall() const {
    return numberParticlesInIntervall;
}

const std::vector<double> &RadialPairDistributionCalculator::getLocalDensities() const {
    return localDensities;
}

RadialPairDistributionCalculator::~RadialPairDistributionCalculator() = default;


void RadialPairDistributionCalculator::calculationResultsToString() {

}
