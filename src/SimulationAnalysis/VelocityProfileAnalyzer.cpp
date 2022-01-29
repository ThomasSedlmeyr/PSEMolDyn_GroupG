#include "VelocityProfileAnalyzer.h"
#include "OutputWriter/CSVWriter.h"
#include <fstream>

VelocityProfileAnalyzer::~VelocityProfileAnalyzer() = default;

VelocityProfileAnalyzer::VelocityProfileAnalyzer(ParticleContainer *particleContainer) : Analyzer(particleContainer) {
    binWidth = XMLParser::domainSize[0] / XMLParser::numberOfBins_p;
    pathToCSVfile = XMLParser::pathToAnalysisFolder_p + "/velocity_density.csv";
}

std::string VelocityProfileAnalyzer::calculationResultsToString() {
    calculateVelocityAndDensityProfile();
    std::string line = "";
    int size = bins.size();
    for (Bin* bin : bins) {
        line += std::to_string(bin->getDensity()) + "," + std::to_string(bin->getMeanVelocity());
        if (size > 1) {
            line += ",";
        }
        size--;
    }
    return line;
}

std::string VelocityProfileAnalyzer::createHeaderLine() {
    std::string line = "d1,v1";
    for (int i = 2; i <= XMLParser::numberOfBins_p; ++i) {
        line += ",d" + std::to_string(i) + ",v" + std::to_string(i);
    }
    return line;
}

void VelocityProfileAnalyzer::calculateVelocityAndDensityProfile() {
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

/*
bool VelocityProfileAnalyzer::appendLineToCSVfile(int timeStep) {

    // append with timestamp
    std::ofstream outputFile;
    outputFile.open("../Analysis_Files/analysisFile.csv", std::ios::app);
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
 */

/*
bool VelocityProfileAnalyzer::createCSV() {
    std::ofstream outputFile;
    outputFile.open("../Analysis_Files/analysisFile.csv", std::ios::trunc);

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
*/

