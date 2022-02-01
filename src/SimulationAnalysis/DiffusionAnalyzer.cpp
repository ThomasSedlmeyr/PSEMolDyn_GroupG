#include "DiffusionAnalyzer.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

void DiffusionAnalyzer::calculateDiffusion() {
    getSimulationParticles();
    sortParticles();

    double difference;
    diffusion = 0;
    if(particles.size() != oldPositions.size()){
        int dsfsd = 0;
    }
    for(int i = 0; i < particles.size(); i++){
        std::array<double, 3> currentPosition = particles[i].getRealPosition();

        double sumOfSquares = 0;
        for(int j = 0; j < 3; j++){
            difference = currentPosition[j] - oldPositions[i][j];
            sumOfSquares += difference * difference;
        }
        if(particles[i].getNumberOfTimesCrossedWholeDomain()[0] > 3 || particles[i].getNumberOfTimesCrossedWholeDomain()[1] > 3
        || particles[i].getNumberOfTimesCrossedWholeDomain()[2] > 1){
            int sdfasy = 0;
        }
        if(particles[i].getId() == 100){
            Particle p = particles[i];
            auto oldPosition = oldPositions[i];
            auto oldPositionX = oldPositions[i][0];
            auto currentPostionX = p.getRealPosition()[0];
            int sdfs = 0;
        }
        //We dived in every step to keep the numbers smaller to have a better floating point accuracy
        //diffusion += sumOfSquares / oldPositions.size();
        diffusion += sumOfSquares;
        //We update the new position
        oldPositions[i] = currentPosition;
        double asdfs = oldPositions[i][0];
        int sdfsdf = 0;
    }
    diffusion /= (1.0 * oldPositions.size());
}

double DiffusionAnalyzer::getDiffusion() const {
    return diffusion;
}

void DiffusionAnalyzer::initializeOldPositions(){
    getSimulationParticles();
    sortParticles();
    int size = particles.size();
    oldPositions = std::vector<std::array<double, 3>>(size);
    for(int i = 0; i < particles.size(); i++){
        oldPositions[i] = particles[i].getRealPosition();
    }
}

DiffusionAnalyzer::~DiffusionAnalyzer() = default;

DiffusionAnalyzer::DiffusionAnalyzer(ParticleContainer *particleContainer) : Analyzer(particleContainer) {
    initializeOldPositions();
    pathToCSVfile = XMLParser::pathToAnalysisFolder_p + "/diffusion.csv";
}

std::string DiffusionAnalyzer::calculationResultsToString() {
    calculateDiffusion();
    return std::to_string(diffusion);
}

std::string DiffusionAnalyzer::createHeaderLine() {
    return "Diffusion";
}

