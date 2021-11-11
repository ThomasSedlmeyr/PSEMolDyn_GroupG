#include "ParticleContainer.h"
#include <outputWriter/VTKWriter.h>
#include <utils/ArrayUtils.h>
#include <iostream>
#include "ParticleContainer.h"

std::vector<Particle> &ParticleContainer::getParticles() {
    return particles;
}

//Code adapted from https://internalpointers.com/post/writing-custom-iterators-modern-cpp

ParticleContainer::Iterator ParticleContainer :: begin() { return Iterator(particles.at(0)); }
ParticleContainer::Iterator ParticleContainer :: end()   { return Iterator(particles.back()); }


void ParticleContainer :: printParticles(){
    int counter = 0;
    for(auto particle : particles){
        std::cout <<"Particle: " << counter << " " << particle << std::endl;
    }
}

Particle &ParticleContainer::Iterator::operator*() const {
     return *m_ptr;
}

ParticleContainer::Iterator::pointer ParticleContainer::Iterator::operator->() {
     return m_ptr;
}

ParticleContainer::Iterator &ParticleContainer::Iterator::operator++() {
    m_ptr++;
    return *this;
}

ParticleContainer::Iterator ParticleContainer::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool operator==(const ParticleContainer::Iterator &a, const ParticleContainer::Iterator &b) {
    return a.m_ptr == b.m_ptr;
}

bool operator!=(const ParticleContainer::Iterator &a, const ParticleContainer::Iterator &b) {
    return a.m_ptr != b.m_ptr;
}
