#include <valarray>
#include <iostream>
#include "Simulation.h"
#include <spdlog/spdlog.h>


bool Simulation::readParamsAndValues(const std::string &fileName) {
    argumentContainer = ArgumentContainer();
    bool couldRaedFile = argumentContainer.readParamsAndValues(fileName);
    if(!couldRaedFile){
        spdlog::error("Could not read Parameter file");
        return false;
    }
    if(!argumentContainer.checkIfParamsMatchParamsAndValues(paramNames)){
        spdlog::error("The Parameter file contains not enough or wrong parameters");
        return false;
    }
    return true;
}

void Simulation::calculateOneTimeStep() {
    particleContainer->updateParticlePositions(posCalcVisitor);
    calculateF();
    particleContainer->walkOverParticles(velCalcVisitor);
}

void Simulation::simulate(const double &endTime, const double &delta_t, Writer &writer, const int &numberSkippedPrintedIterations, const std::string &parametersFileName,
                          const std::string &particlesFileName, const std::string &outputFileName){
    int iteration = 0;
    particleContainer = new ParticleContainerLinkedCells(100, 100, 6, 3);
    //particleContainer = new ParticleContainerDirectSum();
    posCalcVisitor.setDeltaT(delta_t);
    velCalcVisitor.setDeltaT(delta_t);

    double currentTime = 0;

    initializeParamNames();
    //read Paramsfile
    bool couldParseFile = readParamsAndValues(parametersFileName);
    if(!couldParseFile){
        spdlog::error("Could not parse file" + parametersFileName);
        exit(EXIT_FAILURE);;
    }
    setParamsWithValues();
    //read particles file
    couldParseFile = readParticles(particlesFileName);
    if(!couldParseFile){
        spdlog::error("Error in File: " + particlesFileName);
        exit(EXIT_FAILURE);;
    }
    while (currentTime < endTime) {
        calculateOneTimeStep();
        iteration++;
        if (iteration % numberSkippedPrintedIterations == 0) {
            writer.writeParticlesToFile(outputFileName, iteration, particleContainer->getParticles());
        }
        spdlog::info("Iteration " + std::to_string(iteration) + " finished.");
        currentTime += delta_t;
    }
}

Simulation::~Simulation() = default;