//
// Created by thomas on 07.11.21.
//

#include "LennardJonesSimulation.h"
#include "utils/ArrayUtils.h"
#include "Cuboid.h"
#include "Tetrahedron.h"
#include <string>
#include <list>
#include <fstream>
#include "utils/MaxwellBoltzmannDistribution.h"

void LennardJonesSimulation::initializeParamNames() {
    paramNames = {"epsilon", "mass", "rho", "h"};
}

void LennardJonesSimulation::setParamsWithValues() {
    epsilon = argumentContainer.getValueToParam("epsilon");
    mass = argumentContainer.getValueToParam("mass");
    rho = argumentContainer.getValueToParam("rho");
    meshWidth = argumentContainer.getValueToParam("h");
    forceCalcVisitor.setEpsilon(epsilon);
    forceCalcVisitor.setRho(rho);
}

bool LennardJonesSimulation::readParticles(const std::string &fileName) {
    Body* body = nullptr;
    std::ifstream file(fileName);
    std::string line;
    int bodiesCounter = 0;
    numberParticles = 0;
    if(file.is_open()) {
        while ((std::getline(file, line))) {
            //Skip Header
            if (line.at(0) == '#' || line.empty()) continue;
            if (line.compare("Cuboid") == 0) {
                body = new Cuboid(bodiesCounter, meshWidth, mass);
            }
            if (line.compare("Tetrahedron") == 0) {
                body = new Tetrahedron(bodiesCounter, meshWidth, mass);
            }
            if (!std::getline(file, line)) return false;
            body->parsePosition(line);
            if (!std::getline(file, line)) return false;
            body->parseInitialV(line);
            if (!std::getline(file, line)) return false;
            body->parseStructure(line);
            body->generateParticles(numberParticles);

            numberParticles += body->getParticles().size();
            bodies.push_back(body);
            bodiesCounter++;
        }
        file.close();
    }
    uniteParticlesFromBodies();
    return true;
}

void LennardJonesSimulation::uniteParticlesFromBodies() {
    for (Body* body : bodies) {
        for(Particle &particle : body->getParticles()){
            particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(0.1, 3));
            particleContainer->addParticleToContainer(particle);
        }
    }
}


void LennardJonesSimulation::setEpsilon(double epsilon) {
    LennardJonesSimulation::epsilon = epsilon;
}

void LennardJonesSimulation::setRho(double rho) {
    LennardJonesSimulation::rho = rho;
}

void LennardJonesSimulation::calculateF() {
    particleContainer->walkOverParticlePairs(forceCalcVisitor);
}