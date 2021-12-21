#include <valarray>
#include <iostream>
#include "Simulation.h"
#include <spdlog/spdlog.h>
#include "XML_Parser/XMLParser.h"

void Simulation::calculateOneTimeStep() {
    particleContainer->updateParticlePositions(posCalcVisitor);
    calculateF();
    particleContainer->walkOverParticles(velCalcVisitor);
}

void Simulation::simulate(const double &endTime, const double &delta_t, Writer &writer,
                          const int &numberSkippedPrintedIterations, const std::string &inputFile, const std::string &outputFileName,
                          ParticleContainer *partContainer) {
    simulateLogic(endTime, delta_t, writer, numberSkippedPrintedIterations, inputFile, outputFileName, partContainer);
}

void Simulation::simulate(Writer &writer, ParticleContainer *partContainer) {
    simulateLogic(XMLParser::t_end_p, XMLParser::delta_t_p, writer, XMLParser::writeFrequency_p, XMLParser::gravInput_p, XMLParser::baseNameOutputFiles_p, partContainer);
}

void Simulation::simulateLogic(const double &endTime, const double &delta_t, Writer &writer,
                               const int &numberSkippedPrintedIterations, const std::string &inputFile,
                               const std::string &outputFileName, ParticleContainer *partContainer) {
    particleContainer = partContainer;
    posCalcVisitor.setDeltaT(delta_t);
    velCalcVisitor.setDeltaT(delta_t);

    thermostat = Thermostat(particleContainer, XMLParser::T_init_p, XMLParser::delta_T_p);
    int nThermostat = XMLParser::n_thermostat_p;

    int iteration = 0;
    double currentTime = 0;
    //read particles file
    bool couldParseFile = readParticles(inputFile);
    if(!couldParseFile){
        spdlog::error("Error in File: " + inputFile);
        exit(EXIT_FAILURE);;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while (currentTime < endTime) {
        if (iteration % numberSkippedPrintedIterations == 0) {
            writer.writeParticlesToFile(outputFileName, iteration, particleContainer->getParticles());
        }
        if (iteration % nThermostat){
            thermostat.apply();
        }
        calculateOneTimeStep();
        iteration++;
        spdlog::info("Iteration " + std::to_string(iteration) + " finished.");
        currentTime += delta_t;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "Simulation took: " << duration << "ms" << std::endl;
    auto numIterations = XMLParser::t_end_p / XMLParser::delta_t_p;
    std::cout << "Time per iteration: " << double(duration) / numIterations << "ms" << std::endl;
}

Simulation::~Simulation() = default;