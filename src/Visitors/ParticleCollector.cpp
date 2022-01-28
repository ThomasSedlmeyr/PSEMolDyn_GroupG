//
// Created by philip on 30.11.21.
//

#include "ParticleCollector.h"

void ParticleCollector::visitParticle(Particle &p) {
    #ifdef _OPENMP
    #pragma omp critical
    #endif //_OPENMP
    {
        particles.push_back(p);
    }
}

std::vector<Particle> &ParticleCollector::getParticles() {
    return particles;
}
