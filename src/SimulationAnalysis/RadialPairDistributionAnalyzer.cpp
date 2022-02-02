#include "RadialPairDistributionAnalyzer.h"
#include "utils/ArrayUtils.h"
#include "XML_Parser/XMLParser.h"
#include <math.h>

RadialPairDistributionAnalyzer::RadialPairDistributionAnalyzer(ParticleContainer *particleContainer,
                                                               double startOfIntervall, double stepSize,
                                                               int numberOfValues, int startTime, int timeStepSize) : Analyzer(
        particleContainer), startOfIntervall(startOfIntervall), stepSize(stepSize), timeStepSize(timeStepSize) {

    numberParticlesInIntervall = std::vector<int>(numberOfValues);
    localDensities = std::vector<double>(numberOfValues);
    currentTime = startTime;
    pathToCSVfile = XMLParser::pathToAnalysisFolder_p + "/radial_Pair_Distribution.csv";
}

void RadialPairDistributionAnalyzer::calculateLocalDensities() {
    getSimulationParticles();
    for (int & i : numberParticlesInIntervall) {
        i = 0;
    }
    double difference = 0;
    int index = 0;
    for (auto it = particles.begin(); it != particles.end(); it++) {
        for (auto it2 = it + 1; it2 != particles.end(); it2++) {
            Particle p1 = *it;
            Particle p2 = *it2;
            double distance = 0;

            std::array<double, 3> p1RealPosition = p1.getRealPosition();
            std::array<double, 3> p2RealPosition = p2.getRealPosition();

            difference = p1RealPosition[0] - p2RealPosition[0];
            distance = difference * difference;
            difference = p1RealPosition[1] - p2RealPosition[1];
            distance += difference * difference;
            difference = p1RealPosition[2] - p2RealPosition[2];
            distance += difference * difference;

            distance = sqrt(distance);
            index = int((distance - startOfIntervall) / stepSize);

            //We have to check if the index is in our intervall
            if(index < static_cast<int>(numberParticlesInIntervall.size())){
                //We increment the correct particle counter
                numberParticlesInIntervall[index]++;
            }
        }
    }
    //calculation of the local densities
    double ri, riPlusStepSize, riCubic, riPlusStepSizeCubic;
    for(int i = 0; i < static_cast<int>(localDensities.size()); i++) {
        ri = startOfIntervall + i * stepSize;
        riPlusStepSize = ri + stepSize;
        riCubic = ri * ri * ri;
        riPlusStepSizeCubic = riPlusStepSize * riPlusStepSize * riPlusStepSize;
        localDensities[i] = numberParticlesInIntervall[i] / ((4.0 / 3) * M_PI * (riPlusStepSizeCubic - riCubic));
    }
}

const std::vector<int> &RadialPairDistributionAnalyzer::getNumberParticlesInIntervall() const {
    return numberParticlesInIntervall;
}

const std::vector<double> &RadialPairDistributionAnalyzer::getLocalDensities() const {
    return localDensities;
}

RadialPairDistributionAnalyzer::~RadialPairDistributionAnalyzer() = default;


std::string RadialPairDistributionAnalyzer::calculationResultsToString() {
    calculateLocalDensities();
    std::string resultLine = std::to_string(currentTime) + ",";
    for(double localDensity : localDensities){
        resultLine += std::to_string(localDensity) + ",";
    }
    currentTime += timeStepSize;
    return resultLine;
}

std::string RadialPairDistributionAnalyzer::createHeaderLine() {
    std::string headerLine = "Time,";
    double currentDistance = startOfIntervall;
    for(int i = 0; i < static_cast<int>(localDensities.size()); i++){
        headerLine += std::to_string((int) currentDistance) + ",";
        currentDistance += stepSize;
    }
    return headerLine;
}
