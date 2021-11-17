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

std::array<double, 3> LennardJonesSimulation::calculateFBetweenPair(Particle &p1, Particle &p2) {
    auto x1 = p1.getX();
    auto x2 = p2.getX();
    std::array<double, 3> diff{};
    double squaredNorm = 0;
    double singleDiff;
    for (int i = 0; i < 3; ++i) {
        singleDiff = x1[i] - x2[i];
        diff[i] = singleDiff;
        squaredNorm += singleDiff*singleDiff;
    }
    double term1 = -24.0*epsilon/squaredNorm;
    double term2 =  pow(rho/sqrt(squaredNorm), 6);
    double term3 =  term2 - 2 * term2 * term2;
    double scalar = term1 * term3;
    for (double &d:diff) {
        d *= scalar;
    }
    return diff;
}

bool LennardJonesSimulation::readParticles(const std::string &fileName) {
    Body* body;
    std::ifstream file(fileName);
    std::string line;
    int bodiesCounter = 0;
    numberParticles = 0;
    //TODO wenn die Datei Leerzeichen enthaelt gibt es ein Problem
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
    generateAllParticles();
    return true;
}

void LennardJonesSimulation::generateAllParticles(){
    std::vector<Particle> particles(numberParticles);
    int pos = 0;
    for (Body* body : bodies) {
        for(Particle particle : body->getParticles()){
            //TODO bitte alle anschauen
            //Here we create copies for every particle, because we we want all particles to be
            // behind each other in the memory
            //TODO average velocity sollte parameter sein glaub ich
            particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(0.1, 3));
            particles[pos] = particle;
            pos++;
        }
    }
    particleContainer.setParticles(particles);
}

void LennardJonesSimulation::setParamsWithValues() {
    epsilon = argumentContainer.getValueToParam("epsilon");
    mass = argumentContainer.getValueToParam("mass");
    rho = argumentContainer.getValueToParam("rho");
    meshWidth = argumentContainer.getValueToParam("h");

}

void LennardJonesSimulation::initializeParamNames() {
    paramNames = {"epsilon", "mass", "rho", "h"};
}

void LennardJonesSimulation::setEpsilon(double epsilon) {
    LennardJonesSimulation::epsilon = epsilon;
}

void LennardJonesSimulation::setRho(double rho) {
    LennardJonesSimulation::rho = rho;
}
