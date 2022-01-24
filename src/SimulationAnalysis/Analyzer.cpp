//
// Created by thomas on 20.01.22.
//

#include "SimulationAnalysis/Analyzer.h"

void Analyzer::getSimulationParticles() {
    particles.clear();
    std::vector<Particle> particlesWithGhostParticles = particleContainer->getParticles();
    std::copy_if(begin(particlesWithGhostParticles), end(particlesWithGhostParticles), std::back_inserter(particles),
                 [&](Particle const &p) { return !p.isGhostParticle;});
}



Analyzer::Analyzer(ParticleContainer *particleContainer) : particleContainer(particleContainer) {
    getSimulationParticles();
}

void Analyzer::appendLineToCSVFile() {
    std::string line = calculationResultsToString();
    //TODO Hier soll der CSV-Writer aufgerufen werden mit dem pathToCSVfile
}

void Analyzer::writeHeaderLineToCSVFile() {
    std::string line = createHeaderLine();
    //TODO Hier soll der CSV-Writer aufgerufen werden mit dem pathToCSVfile
}

Analyzer::~Analyzer() = default;
