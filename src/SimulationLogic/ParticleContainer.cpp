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
        std::cout <<"Particle: " << counter << " " << particle << std::endl;
    }
}

