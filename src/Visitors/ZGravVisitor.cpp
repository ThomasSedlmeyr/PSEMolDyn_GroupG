//
// Created by philip on 16.12.21.
//

#include "ZGravVisitor.h"

void ZGravVisitor::visitParticle(Particle &p) {
    if (std::find(particlesWithZGrav.begin(), particlesWithZGrav.end(), p.getId()) != particlesWithZGrav.end()){
        auto &fRef = p.getFRef();
        //TODO faktor aus XML parsen
        fRef[2] += p.getM() * -0.001;
    }
}

void ZGravVisitor::setParticlesWithZGrav(const std::vector<int> &particlesWithZGrav) {
    ZGravVisitor::particlesWithZGrav = particlesWithZGrav;
}