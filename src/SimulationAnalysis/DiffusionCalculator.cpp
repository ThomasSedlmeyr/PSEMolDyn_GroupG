#include "DiffusionCalculator.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

void DiffusionCalculator::calculateDiffusion() {
    getSimulationParticles();

    double difference;
    diffusion = 0;
    for(int i = 0; i < particles.size(); i++){
        std::array<double, 3> currentPosition = {0,0,0};
        currentPosition[0] = particles[i].getX()[0] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[0] * ParticleContainerLinkedCells::domainSizeX;
        currentPosition[1] = particles[i].getX()[1] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[1] * ParticleContainerLinkedCells::domainSizeY;
        currentPosition[2] = particles[i].getX()[2] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[2] * ParticleContainerLinkedCells::domainSizeZ;

        double sumOfSquares = 0;
        for(int j = 0; j < 3; j++){
            difference = currentPosition[j] - oldPositions[i][j];
            sumOfSquares += difference * difference;
        }
        //We dived in every step to keep the numbers smaller to have a better floating point accuracy
        diffusion += sumOfSquares / oldPositions.size();
        //We update the new position
        oldPositions[i] = currentPosition;
    }
}

double DiffusionCalculator::getDiffusion() const {
    return diffusion;
}

void DiffusionCalculator::initializeOldPositions(){
    int size = particles.size();
    oldPositions = std::vector<std::array<double, 3>>(size);
    oldPositions[2] = {0,2,2};
    for(int i = 0; i < particles.size(); i++){
        //Hier möchte ich aber eine echte kopie
        std::array<double, 3> oldPosition = {0,0,0};
        oldPosition[0] = particles[i].getX()[0] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[0] * ParticleContainerLinkedCells::domainSizeX;
        oldPosition[1] = particles[i].getX()[1] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[1] * ParticleContainerLinkedCells::domainSizeY;
        oldPosition[2] = particles[i].getX()[2] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[2] * ParticleContainerLinkedCells::domainSizeZ;
        oldPositions[i] = oldPosition;
    }
}

DiffusionCalculator::~DiffusionCalculator() = default;

void DiffusionCalculator::calculationResultsToString() {
}

DiffusionCalculator::DiffusionCalculator(ParticleContainer *particleContainer) : Calculator(particleContainer) {
    initializeOldPositions();
}

