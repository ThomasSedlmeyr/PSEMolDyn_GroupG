#include "DiffusionCalculator.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

void DiffusionCalculator::calculateDiffusion() {
    updateParticles();

    std::vector<Particle> simulationParticlesOnly;
    double difference;
    double sum = 0;

    for(int i = 0; i < simulationParticlesOnly.size(); i++){
        std::array<double, 3> currentPosition;
        currentPosition[0] = simulationParticlesOnly[i].getX()[0] +
                             simulationParticlesOnly[i].getNumberOfTimesCrossedWholeDomain()[0] * ParticleContainerLinkedCells::domainSizeX;
        currentPosition[1] = simulationParticlesOnly[i].getX()[1] +
                             simulationParticlesOnly[i].getNumberOfTimesCrossedWholeDomain()[1] * ParticleContainerLinkedCells::domainSizeY;
        currentPosition[2] = simulationParticlesOnly[i].getX()[2] +
                             simulationParticlesOnly[i].getNumberOfTimesCrossedWholeDomain()[2] * ParticleContainerLinkedCells::domainSizeZ;

        double sumOfSquares = 0;
        for(int j = 0; j < 3; j++){
            difference = currentPosition[j] - oldPositions[i][j];
            sumOfSquares += difference * difference;
        }
        //We dived in every step to keep the numbers smaller to have a better floating point accuracy
        sum += sqrt(sumOfSquares) / oldPositions.size();
        //We update the new position
        oldPositions[i] = currentPosition;
    }
}

void DiffusionCalculator::initializeOldPositions(){
    //TODO hier würde eigentlich eine Reference genügen aber ich glaube hier werden alle Partikel kopiert
    updateParticles();
    for(int i = 0; i < particles.size(); i++){
        //Hier möchte ich aber eine echte kopie
        oldPositions[i][0] = particles[i].getX()[0] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[0] * ParticleContainerLinkedCells::domainSizeX;
        oldPositions[i][1] = particles[i].getX()[1] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[1] * ParticleContainerLinkedCells::domainSizeY;
        oldPositions[i][2] = particles[i].getX()[2] +
                particles[i].getNumberOfTimesCrossedWholeDomain()[2] * ParticleContainerLinkedCells::domainSizeZ;
    }
}

DiffusionCalculator::~DiffusionCalculator() = default;

void DiffusionCalculator::calculationResultsToString() {

}

DiffusionCalculator::DiffusionCalculator(){
    initializeOldPositions();
}
