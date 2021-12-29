//
// Created by thomas on 29.12.21.
//

#include "Membrane.h"

void Membrane::parseStructure(const std::string &line) {

}

void Membrane::generateParticles(int startIndex) {
    particles = std::vector<Particle>(dimensions[0] * dimensions[1] * dimensions[2]);
    std::array<double, 3> newPosition{};
    int counter = 0;
    for (int i = 0; i < dimensions[0]; ++i) {
        for (int j = 0; j < dimensions[1]; ++j) {
            for (int k = 0; k < dimensions[2]; ++k) {
                newPosition[0] = position[0] + meshWidth * i;
                newPosition[1] = position[1] + meshWidth * j;
                newPosition[2] = position[2] + meshWidth * k;
                particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startIndex);
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

}

/*void Membrane::setParticlesWhereFisApplied(int startIndex) {
    int indexOfBody;
    for(auto& position : positionsWhereFisApplied){
        indexOfBody = position[0] + position[1] * dimensions[0];
        particles[indexOfBody] = 0;
    }
}*/
