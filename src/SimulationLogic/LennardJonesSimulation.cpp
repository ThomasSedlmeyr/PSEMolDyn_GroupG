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
    std::vector<Particle> particles(numberParticles);
    int pos = 0;
    for (Body* body : bodies) {
        for(Particle particle : body->getParticles()){
            //Here we create copies for every particle, because we want all particles to be
            // behind each other in the memory
            particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(0.1, 3));
            particles[pos] = particle;
            pos++;
        }
    }
    particleContainer.setParticles(particles);
}

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
    double term2 =  (rho*rho*rho*rho*rho*rho) / (squaredNorm * squaredNorm * squaredNorm);
    double term3 =  term2 - 2 * term2 * term2;
    double scalar = term1 * term3;

    for (double &d:diff) {
        d *= scalar;
    }
    return diff;
}

void LennardJonesSimulation::calculateFFast(){
    std::vector<Particle> &particles = particleContainer.getParticles();
    particles[0].prepareForNewForce();
    auto firstParticle = particles.begin();
    for (auto p1 = firstParticle; p1 != particles.end(); ++p1){
        for (auto p2 = p1 + 1; p2 != particles.end(); ++p2){
            if (p1==firstParticle){
                //this is only reached the first time the Particle p2 is used, so it has to be prepared here
                p2->prepareForNewForce();
            }
            //fij is force between the particles p1 and p2
            auto fij = calculateFBetweenPair(*p1, *p2);
            auto &f1 = p1->getFRef();
            auto &f2 = p2->getFRef();
            //faster than using ArrayUtils
            double temp;
            for (int i = 0; i < 3; ++i) {
                temp = fij[i];
                f1[i] += temp;
                f2[i] -= temp;
            }
        }
    }
}

void LennardJonesSimulation::setEpsilon(double epsilon) {
    LennardJonesSimulation::epsilon = epsilon;
}

void LennardJonesSimulation::setRho(double rho) {
    LennardJonesSimulation::rho = rho;
}
