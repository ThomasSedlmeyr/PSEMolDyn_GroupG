//
// Created by thomas on 20.01.22.
//

#include "Calculator.h"

void Calculator::getSimulationParticles() {
    particles.clear();
    std::vector<Particle> particlesWithGhostParticles = particleContainer->getParticles();
    std::copy_if(begin(particlesWithGhostParticles), end(particlesWithGhostParticles), std::back_inserter(particles),
                 [&](Particle const &p) { return !p.isGhostParticle;});
}

void Calculator::appendLineToCSVFile(std::string& name) {

}

Calculator::Calculator(ParticleContainer *particleContainer) : particleContainer(particleContainer) {
    getSimulationParticles();
}

Calculator::~Calculator() = default;
