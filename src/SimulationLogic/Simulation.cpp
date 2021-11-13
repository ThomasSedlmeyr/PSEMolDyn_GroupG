#include <valarray>
#include <iostream>
#include "Simulation.h"
#include <utils/ArrayUtils.h>
#include <functional>

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

void Simulation::simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedIterations, const std::string &parametersFileName,
                          const std::string &particlesFileName, const std::string &outPutFileName){
    int iteration = 0;
    double currentTime = 0;

    initializeParamNames();
    readParamsAndValues(parametersFileName);
    //this methode could only be implemented in the subclasses
    setParamsWithValues();
    readParticles(particlesFileName);

    while (currentTime < endTime) {
        calculateOneTimeStep(delta_t);

        iteration++;
        if (iteration % numberSkippedIterations == 0) {
            //particleContainer.plotParticles(iteration);
            writer.writeParticlesToFile(outPutFileName, iteration, particleContainer.getParticles());
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;
        currentTime += delta_t;
    }
}

const ParticleContainer Simulation::getParticleContainer() const {
    return particleContainer;
}


void Simulation::readParamsAndValues(const std::string &fileName) {
    argumentContainer = ArgumentContainer();
    argumentContainer.readParamsAndValues(fileName);

    if(!argumentContainer.checkIfParamsMatchParamsAndValues(paramNames)){
        //Fehlerbehandlung mit throws oder so änlich
    }

}

void Simulation::calculateF() {
    particleContainer.applyFToParticlePairs(callForceCalculation);
}