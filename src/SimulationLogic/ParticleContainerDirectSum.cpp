#include "ParticleContainerDirectSum.h"


void ParticleContainerDirectSum::walkOverParticles(ParticleVisitor &v) {
    for (Particle &p : particles) {
        v.visitParticle(p);
    }
}

void ParticleContainerDirectSum::walkOverParticlePairs(ParticlePairVisitor &visitor) {
    particles[0].prepareForNewForce();
    auto firstParticle = particles.begin();
    for (auto p1 = firstParticle; p1 != particles.end(); ++p1){
        for (auto p2 = p1 + 1; p2 != particles.end(); ++p2){
            visitor.visitParticlePair(*p1, *p2);
        }
    }
}

void ParticleContainerDirectSum::addParticleToContainer(Particle &p) {
    particles.push_back(p);
}

std::vector<Particle> & ParticleContainerDirectSum::getParticles() {
    return particles;
}

void ParticleContainerDirectSum::setParticles(const std::vector<Particle> &particles) {
    ParticleContainerDirectSum::particles = particles;
}

void ParticleContainerDirectSum::updateParticlePositions(ParticleVisitor &visitor) {
    walkOverParticles(visitor);
}
