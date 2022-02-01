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
    int numbersdfa = particlesWithGhostParticles.size();
    std::copy_if(begin(particlesWithGhostParticles), end(particlesWithGhostParticles), std::back_inserter(particles),
                 [&](Particle const &p) { return !p.isGhostParticle;});
}



Analyzer::Analyzer(ParticleContainer *particleContainer) : particleContainer(particleContainer) {
    writer = new CSVWriter();
}

void Analyzer::appendLineToCSVFile() {
    std::string line = calculationResultsToString();
    writer->writeToFile(pathToCSVfile, line);
}

void Analyzer::writeHeaderLineToCSVFile() {
    std::string line = createHeaderLine();
    writer->createCSV(pathToCSVfile);
    writer->writeToFile(pathToCSVfile, line);
}

void Analyzer::setParticleContainer(ParticleContainer* particleContainer_new) {
    particleContainer = particleContainer_new;
    getSimulationParticles();
}

void Analyzer::sortParticles(){
    std::sort(std::begin(particles),
              std::end(particles),
              [](const Particle &p1, const Particle &p2) { return p1.getId() < p2.getId(); });
}
Analyzer::~Analyzer() = default;