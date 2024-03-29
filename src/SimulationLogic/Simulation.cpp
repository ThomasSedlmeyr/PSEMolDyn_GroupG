#include <valarray>
#include <iostream>
#include "Simulation.h"
#include <spdlog/spdlog.h>
#include "XML_Parser/XMLParser.h"
#include "Checkpoints/CheckpointReader.h"
#include "Checkpoints/CheckpointWriter.h"
#include "Visitors/ParticleCollector.h"
#include "GeometricObjects/Membrane.h"
#include "SimulationAnalysis/VelocityProfileAnalyzer.h"
#include "SimulationAnalysis/DiffusionAnalyzer.h"
#include "SimulationAnalysis/RadialPairDistributionAnalyzer.h"

void Simulation::calculateOneTimeStep(double currentTime) {
    particleContainer->updateParticlePositions(posCalcVisitor);
    if (currentTime < t_lift_end){
        particleContainer->applyFZUp();
    }
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
    const bool useThermostat = XMLParser::useThermostat_p;
    const int nThermostat = XMLParser::n_thermostat_p;
    if (useThermostat){
        setupThermostat();
    }

    if (XMLParser::loadCheckpoint_p){
        //read particles from checkpoint
        if (!CheckpointReader::readCheckpointFile(XMLParser::pathInCheckpoint_p, particleContainer)){
            spdlog::error("Error in checkpoint file: " + XMLParser::pathInCheckpoint_p);
            exit(EXIT_FAILURE);;
        }
    }
    //read particles from file
    if (!readParticles(inputFile)){
        spdlog::error("Error in File: " + inputFile);
        exit(EXIT_FAILURE);;
    }

    int iteration = 0;
    double currentTime = 0;
    int numberOfTimeStepsToAnalyzeDiffusions = 1000;
    int numberOfTimeStepsToAnalyzeVelocityProfiles = 10000;

    VelocityProfileAnalyzer* velocityAnalyzer = nullptr;
    DiffusionAnalyzer* diffusionAnalyzer = nullptr;
    RadialPairDistributionAnalyzer* rdfAnalyzer = nullptr;
    ParticleContainerLinkedCells* particleContainerLinkedCells = nullptr;

    if(XMLParser::useProfiling_p){
        velocityAnalyzer = new VelocityProfileAnalyzer(partContainer);
        diffusionAnalyzer = new DiffusionAnalyzer(partContainer);
        rdfAnalyzer = new RadialPairDistributionAnalyzer(partContainer, 0, 0.5, 50, 5, 20);
        velocityAnalyzer->writeHeaderLineToCSVFile();
        diffusionAnalyzer->writeHeaderLineToCSVFile();
        rdfAnalyzer->writeHeaderLineToCSVFile();
        if (XMLParser::parallelType_p == SECONDPARALLEL){
            particleContainerLinkedCells = dynamic_cast<ParticleContainerLinkedCells*>(partContainer);
            particleContainerLinkedCells->writeHeaderFileOfParticlesCount();
        }
    }
    writer.writeParticlesToFile(outputFileName, iteration, particleContainer->getParticles());
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while (currentTime < endTime) {
        if(XMLParser::useProfiling_p && iteration % numberOfTimeStepsToAnalyzeVelocityProfiles == 0){
            if (velocityAnalyzer != nullptr){
                velocityAnalyzer->appendLineToCSVFile();
            }
        }
        if(iteration % numberOfTimeStepsToAnalyzeDiffusions == 0 && XMLParser::useProfiling_p){
            if (XMLParser::parallelType_p == SECONDPARALLEL){
                particleContainerLinkedCells->countParticlesInSubdomains();
            }
            if (diffusionAnalyzer != nullptr){
                diffusionAnalyzer->appendLineToCSVFile();
            }
            if (rdfAnalyzer != nullptr){
                rdfAnalyzer->appendLineToCSVFile();
            }
        }
        if (iteration != 0 && iteration % numberSkippedPrintedIterations == 0) {
            writer.writeParticlesToFile(outputFileName, iteration, particleContainer->getParticles());
            std::cout << "Iteration: " << iteration << std::endl;
        }
        if (iteration != 0 && useThermostat){
            if (iteration % nThermostat == 0){
                thermostat.apply();
            }
        }
        calculateOneTimeStep(currentTime);
        iteration++;
        spdlog::info("Iteration " + std::to_string(iteration) + " finished.");
        currentTime += delta_t;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "Simulation took: " << duration << "ms" << std::endl;
    auto numIterations = XMLParser::t_end_p / XMLParser::delta_t_p;
    std::cout << "Time per iteration: " << double(duration) / numIterations << "ms" << std::endl;
    ParticleCollector particleCollector = ParticleCollector();
    particleContainer->walkOverParticles(particleCollector);
    int numberOfParticles = static_cast<int> (particleCollector.getParticles().size());
    double mups = (numIterations * numberOfParticles) / (static_cast<double>(duration) / 1000.0);
    std::cout << (mups / 1000000.0) << " MMUPS/s"<< std::endl;
    if (XMLParser::makeCheckpoint_p){
        CheckpointWriter::writeCheckpointFile(XMLParser::pathOutCheckpoint_p, particleContainer);
    }
}

void Simulation::setupThermostat() {
    auto targetTemp =  XMLParser::T_init_p;
    if (XMLParser::T_target_p != -1){
        targetTemp = XMLParser::T_target_p;
    }
    auto maxDeltaT = XMLParser::delta_T_p;
    if (maxDeltaT == -1){
        //unlimited maxDeltaT
        thermostat = Thermostat(particleContainer, targetTemp, XMLParser::dimensionType_p);
    }else{
        //limited maxDeltaT
        thermostat = Thermostat(particleContainer, targetTemp, XMLParser::dimensionType_p, maxDeltaT);
    }
}

Simulation::~Simulation() = default;