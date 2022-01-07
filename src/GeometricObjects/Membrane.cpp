//
// Created by thomas on 29.12.21.
//

#include <Visitors/LJForceVisitor.h>
#include <Visitors/UpwardForceVisitor.h>
#include "Membrane.h"

void Membrane::parseStructure(const std::string &line) {
    dimensions = parseLineWithThreeValues(line);
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
    setNeighbourParticles();
    setParticlesWhereFisApplied();
}

Membrane::Membrane(int ID, double meshWidth, double massPerParticle) : Body(ID, meshWidth, massPerParticle) {
    LJForceVisitor::membraneIDs.push_back(ID);
    //TODO LÖSCHEN!!!!!!!
    positionsWhereFisApplied = {{17,24},{17,25},{18,24},{18,25}};
    //TODO LÖSCHEN!!!!!!!
}

Membrane::~Membrane() {}

void Membrane::setParticlesWhereFisApplied() {
    for(auto& position : positionsWhereFisApplied){
        int index = position[0] + position[1] * dimensions[0];
        UpwardForceVisitor::particlesWithFZUp.push_back(particles[index].getId());
    }
}

void Membrane::setNeighbourParticles() {
    for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
        auto topNeighbour = i + int(dimensions[0]);
        auto bottomNeighbour = i - int(dimensions[0]);
        if (topNeighbour >= particles.size()){
            topNeighbour = -2;
        }
        if (bottomNeighbour < 0){
            bottomNeighbour = -2;
        }

        //Vertical neighbours
        particles[i].addParticleToNeighbours(topNeighbour);
        particles[i].addParticleToNeighbours(bottomNeighbour);

        particles[i].addParticleToDirectNeighbours(topNeighbour);
        particles[i].addParticleToDirectNeighbours(bottomNeighbour);

        if (i % int(dimensions[0]) != 0){
            //Not on left edge
            particles[i].addParticleToNeighbours(i-1);
            particles[i].addParticleToDirectNeighbours(i-1);
            //diagonal neighbours
            particles[i].addParticleToNeighbours(topNeighbour - 1);
            particles[i].addParticleToNeighbours(bottomNeighbour - 1);
        }

        if ((i + 1) % int(dimensions[0]) != 0){
            //Not on right edge
            particles[i].addParticleToNeighbours(i+1);
            particles[i].addParticleToDirectNeighbours(i+1);
            //diagonal neighbours
            particles[i].addParticleToNeighbours(topNeighbour + 1);
            particles[i].addParticleToNeighbours(bottomNeighbour + 1);
        }
    }
}