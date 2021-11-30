//
// Created by philip on 30.11.21.
//

#include "ParticleCollector.h"

void ParticleCollector::visitParticle(Particle &p) {
    particles.push_back(p);
}

std::vector<Particle> &ParticleCollector::getParticles() {
    return particles;
}
