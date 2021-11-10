#include <valarray>
#include <iostream>
#include "Simulation.h"
#include <utils/ArrayUtils.h>

Simulation::Simulation() = default;
Simulation::~Simulation() = default;

void Simulation::calculateX(const double &delta_t) {
    for (auto &p: particleContainer.getParticles()) {
        p.setX(p.getX() + delta_t * p.getV() + pow(delta_t, 2) / (2 * p.getM()) * p.getF());
    }
}

void Simulation::calculateV(const double &delta_t) {
    for (auto &p: particleContainer.getParticles()) {
        p.setV(p.getV() + (delta_t / (2 * p.getM())) * (p.getOldF() + p.getF()));
    }
}

void Simulation::calculateOneTimeStep(const double &delta_t){
    calculateX(delta_t);
    calculateF();
    calculateV(delta_t);
}

void Simulation::simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedIterations, char *filename){
    int iteration = 0;
    double currentTime = 0;

    readInputFile(filename);

    while (currentTime < endTime) {
        calculateOneTimeStep(delta_t);

        iteration++;
        if (iteration % numberSkippedIterations == 0) {
            //particleContainer.plotParticles(iteration);
            writer.writeParticlesToFile("Grav", iteration, particleContainer.getParticles());
        }

        std::cout << "Iteration " << iteration << " finished." << std::endl;
        currentTime += delta_t;
    }
}

const ParticleContainer Simulation::getParticleContainer() const {
    return particleContainer;
}
