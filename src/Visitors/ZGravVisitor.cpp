//
// Created by philip on 16.12.21.
//

#include "ZGravVisitor.h"

std::vector<int> ZGravVisitor::particlesWithZGrav{};
//TODO faktor aus XML parsen
double ZGravVisitor::gGrav = -0.001;

void ZGravVisitor::visitParticle(Particle &p) {
    if (std::find(particlesWithZGrav.begin(), particlesWithZGrav.end(), p.getId()) != particlesWithZGrav.end()){
        auto &fRef = p.getFRef();
        fRef[2] += p.getM() * gGrav;
    }
}

void ZGravVisitor::setParticlesWithZGrav(const std::vector<int> &particlesWithZGrav) {
    ZGravVisitor::particlesWithZGrav = particlesWithZGrav;
}