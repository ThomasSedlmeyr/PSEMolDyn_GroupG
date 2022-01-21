//
// Created by thomas on 20.01.22.
//

#include "Calculator.h"

void Calculator::updateParticles() {
    std::vector<Particle> particlesWithGhostParticles = particleContainer.getParticles();

    std::copy_if(begin(particlesWithGhostParticles), end(particlesWithGhostParticles), std::back_inserter(particles),
                 [&](Particle const &p) { return !p.isGhostParticle;});
}

void Calculator::appendLineToCSVFile(std::string& name) {

}

Calculator::~Calculator() = default;
