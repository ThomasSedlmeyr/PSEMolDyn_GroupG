//
// Created by thomas on 07.11.21.
//

#include "LennardJonesSimulation.h"
#include "utils/ArrayUtils.h"
#include "GeometricObjects/Cuboid.h"
#include <string>
#include "utils/MaxwellBoltzmannDistribution.h"
#include "XML_Parser/XMLParser.h"

bool LennardJonesSimulation::readParticles(const std::string &fileName) {
    forceCalcVisitor.setEpsilon(XMLParser::epsilon_p);
    forceCalcVisitor.setRho(XMLParser::rho_p);
    uniteParticlesFromBodies();
    return true;
}

void LennardJonesSimulation::uniteParticlesFromBodies() {
    for (Body* body : XMLParser::bodies_p) {
        for(Particle &particle : body->getParticles()){
            particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(0.1, 2));
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