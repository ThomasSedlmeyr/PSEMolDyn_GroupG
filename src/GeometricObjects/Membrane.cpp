//
// Created by thomas on 29.12.21.
//

#include "Membrane.h"
#include "utils/ArrayUtils.h"

void Membrane::parseStructure(const std::string &line) {

}

void Membrane::generateParticles(int startIndex) {
    particles = std::vector<Particle>(dimensions[0] * dimensions[1] * dimensions[2]);
    std::array<double, 3> newPosition{};
    int counter = 0;
    for (int i = 0; i < dimensions[0]; ++i) {
        for (int j = 0; j < dimensions[1]; ++j) {
            for (int l = 0; l < dimensions[2]; ++l) {
                newPosition[0] = position[0] + meshWidth * i;
                newPosition[1] = position[1] + meshWidth * j;
                newPosition[2] = position[2] + meshWidth * l;
                particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startIndex, movingIsAllowed);
                startIndex++;
                counter++;
            }
        }
    }
}

Membrane::Membrane(int ID, double meshWidth, double massPerParticle) : Body(ID, meshWidth, massPerParticle) {

}

Membrane::~Membrane() {}

void Membrane::applyTheHarmonicPotential() {
    for (int i = 0; i < particles.size(); ++i) {
        for (int j = i + 1; j < particles.size(); ++j) {
            auto norm = ArrayUtils::L2Norm(particles[i].getX() - particles[j].getX());
            auto fij = k * (norm - sqrt(2) * rZero) * (particles[j].getX() - 1/norm * particles[i].getX());
        }
    }
}

void Membrane::setParticlesWhereFisApplied() {
    for(auto& position : positionsWhereFisApplied){
        int index = position[0] + position[1] * dimensions[0];
        particlesWhereFisApplied.push_back(particles[index].getId());
    }
}
