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

std::array<double, 3> LennardJonesSimulation::calculateFBetweenPair(Particle &p1, Particle &p2) {
    auto norm = ArrayUtils::L2Norm(p1.getX() - p2.getX());
    double term1 = -24*epsilon/pow(norm, 2);
    double term2 =  pow(rho/norm, 6);
    double term3 =  term2 - 2 * pow(term2, 2);
    return term1 * term3 * (p2.getX() - p1.getX());
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
            /*if (line.compare("Tetrahedron") == 0) {
                body = new Tetrahedron(bodiesCounter, meshWidth);
            }*/
            if (!std::getline(file, line)) return false;
            body->parsePosition(line);
            if (!std::getline(file, line)) return false;
            body->parseInitialV(line);
            if (!std::getline(file, line)) return false;
            body->parseStructure(line);
            body->generateParticles();

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
    for (Body* body : bodies) {
        for(Particle particle : body->getParticles())
            //TODO bitte alle anschauen
            //Here we create copies for every particle, because we we want all particles to be
            // behind each other in the memory
            particles.push_back(particle);
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


