//
// Created by thomas on 07.11.21.
//

#include "LennardJonesSimulation.h"
#include "utils/ArrayUtils.h"
#include "GeometricObjects/Cuboid.h"
#include <string>
#include "utils/MaxwellBoltzmannDistribution.h"
#include "XML_Parser/XMLParser.h"
#include "XML_Parser/BodyBuilder.h"

bool LennardJonesSimulation::readParticles(const std::string &fileName) {
    BodyBuilder::buildBodies(XMLParser::bodies_p, XMLParser::bodySequence);
    uniteParticlesFromBodies();
    return true;
}

void LennardJonesSimulation::uniteParticlesFromBodies() {
    for (Body* body : XMLParser::bodies_p) {
        for(Particle &particle : body->getParticles()){
            if (XMLParser::useBrownianMotion_p){
                auto factor = sqrt(tInit / particle.getM());
                particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(factor, dimensions));
            }else{
                particle.setV(particle.getV() + maxwellBoltzmannDistributedVelocity(0.1, dimensions));
            }
            particleContainer->addParticleToContainer(particle);
        }
    }
}

void LennardJonesSimulation::calculateF() {
    particleContainer->walkOverParticlePairs(forceCalcVisitor);
}