#include "ParticleContainer.h"
#include <outputWriter/VTKWriter.h>
#include <utils/ArrayUtils.h>
#include <iostream>
#include "ParticleContainer.h"

std::vector<Particle> &ParticleContainer::getParticles() {
    return particles;
}


void ParticleContainer :: printParticles(){
    int counter = 0;
    for(auto particle : particles){
        std::cout << particle.toString() << std::endl;
    }
}

void ParticleContainer::setParticles(const std::vector<Particle> &particles) {
    ParticleContainer::particles = particles;
}

void ParticleContainer::applyFToParticlePairs(const std::function<std::array<double, 3>(Particle&, Particle&)>& f) {
    particles[0].prepareForNewForce();
    auto firstParticle = particles.begin();
    for (auto p1 = firstParticle; p1 != particles.end(); ++p1){
        for (auto p2 = p1 + 1; p2 != particles.end(); ++p2){
            if (p1==firstParticle){
                //this is only reached the first time the Particle p2 is used, so it has to be prepared here
                p2->prepareForNewForce();
            }
            //fij is force between the particles p1 and p2
            auto fij = f(*p1, *p2);
            p1->setF(p1->getF()+fij);
            //since Fij = -Fji - is used here instead of +
            p2->setF(p2->getF()-fij);
        }
    }

}
