#include "SimulationAnalyzer.h"
#include <fstream>

/*
 * first call createCSV
 * then repeatedly call calculate + appendLine
 */

bool SimulationAnalyzer::appendLineToCSVfile(int timeStep) {

    // append with timestamp
    std::ofstream outputFile;
    outputFile.open("../SimulationAnalysis_Files/analysisFile.csv", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << timeStep;
        // ordered correctly? use list instead?
        for (Bin* tempBin : bins) {
            // outputFile << ",d" << tempBin->getDensity() << ",v" << tempBin->getMeanVelocity();
            outputFile << "," << tempBin->getDensity() << "," << tempBin->getMeanVelocity();
        }
        outputFile << "\n";
        outputFile.close();
    } else {
        return false;
    }
    return true;
}

void SimulationAnalyzer::calculateVelocityAndDensityProfile(ParticleContainer *particleContainer) {
    std::vector<Particle> particles = particleContainer->getParticles();

    double binWidth = XMLParser::domainSize[0] / XMLParser::numberOfBins_p;

    bins.clear();

    for (int i = 1; i <= XMLParser::numberOfBins_p; ++i) {
        Bin* bin = new Bin();
        std::vector<Particle> particles_bin;
        for (Particle particle : particles) {
            // get particles for specific bin that are moving
            if (particle.getX()[0] <= (i * binWidth) && particle.getX()[0] > ((i - 1) * binWidth) && particle.getMovingAllowed() && particle.getV()[1] != 0) {
                particles_bin.push_back(particle);
            }
        }
        bin->setParticles(particles_bin);
        bin->calculateDensity();
        bin->calculateVelocity();
        bins.push_back(bin);
    }
}

bool SimulationAnalyzer::createCSV() {
    std::ofstream outputFile;
    outputFile.open("../SimulationAnalysis_Files/analysisFile.csv", std::ios::trunc);

    if (outputFile.is_open()) {
        // write first line
        outputFile << "timeStep";
        for (int i = 1; i <= XMLParser::numberOfBins_p; ++i) {
            outputFile << ",d" << i << ",v" << i;
        }
        outputFile << "\n";
        outputFile.close();
        return true;
    } else {
        return false;
    }
}
