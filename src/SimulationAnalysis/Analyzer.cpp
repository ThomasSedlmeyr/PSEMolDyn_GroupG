//
// Created by thomas on 20.01.22.
//

#include <fstream>
#include "SimulationAnalysis/Analyzer.h"
#include "XML_Parser/XMLParser.h"
#include "OutputWriter/CSVWriter.h"

void Analyzer::getSimulationParticles() {
    particles.clear();
    std::vector<Particle> particlesWithGhostParticles = particleContainer->getParticles();
    std::copy_if(begin(particlesWithGhostParticles), end(particlesWithGhostParticles), std::back_inserter(particles),
                 [&](Particle const &p) { return !p.isGhostParticle;});
}



Analyzer::Analyzer(ParticleContainer *particleContainer) : particleContainer(particleContainer) {
    getSimulationParticles();
    writer = new CSVWriter(); // TODO CSV files for all?
}

void Analyzer::appendLineToCSVFile() {
    std::string line = calculationResultsToString();
    //TODO Hier soll der CSV-Writer aufgerufen werden mit dem pathToCSVfile
    writer->writeToFile(pathToCSVfile, line);
}

void Analyzer::writeHeaderLineToCSVFile() {
    std::string line = createHeaderLine();
    //TODO Hier soll der CSV-Writer aufgerufen werden mit dem pathToCSVfile
    writer->createCSV(pathToCSVfile);
    writer->writeToFile(pathToCSVfile, line);
}

void Analyzer::setParticleContainer(ParticleContainer* particleContainer_new) {
    particleContainer = particleContainer_new;
    getSimulationParticles();
}

Analyzer::~Analyzer() = default;