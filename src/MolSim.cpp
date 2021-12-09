/**
 * @file MolSim.cpp
 * @brief Main class for Simulation
 */

#include "SimulationLogic/GravitationSimulation.h"
#include "OutputWriter/Writer.h"
#include <iostream>
#include <OutputWriter/VTKWriter.h>
#include <SimulationLogic/LennardJonesSimulation.h>
#include <spdlog/spdlog.h>
#include <XML_Parser/XMLParser.h>

std::string inputFile = "../src/XML_Parser/input.xml";

/**
 * @brief shows guidelines for correct program calls
 */
void show_help();

/**
 * @brief parsing of program parameters
 * @param argc number of parameters
 * @param argsv parameters from command line
 * @return true if successful, false if something went wrong
 */
bool parseCommandLineArguments(int argc, char *argsv[]);

int main(int argc, char *argsv[]) {
    //useful for testing performance
    //spdlog::set_level(spdlog::level::off);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::cout << "Hello from MolSim for PSE!" << std::endl;
    // cases in which correct programme call is not possible
    if (argc < 1) {
        std::cout << "Erroneous programme call! " << std::endl;
        show_help();
        return 0;
    }

    // parsing of potential parameters
    bool success = parseCommandLineArguments(argc, argsv);

    // prints help in case of wrong call
    if (!success) {
        show_help();
        return 0;
    }
    // execution of simulation based to default or selection
    XMLParser::parseXML(inputFile);
    Writer *w = new VTKWriter();
    switch (XMLParser::calcType_p) {
        case Simulation::GRAVITATION: {
            auto gS = GravitationSimulation();
            ParticleContainer *particleContainer = new ParticleContainerDirectSum();
            gS.simulate(*w, particleContainer);
            break;
        }
        case Simulation::LENNARDJONES: {
            auto ljS = LennardJonesSimulation();
            ParticleContainer* particleContainer;
            if (XMLParser::particleContainerType == ParticleContainer::DIRECTSUM){
                particleContainer = new ParticleContainerDirectSum();
            }else if (XMLParser::particleContainerType == ParticleContainer::LINKEDCELLS){
                particleContainer = new ParticleContainerLinkedCells(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::domainSize[2], XMLParser::cutoffRadius, XMLParser::boundaryConditions);
            }else{
                spdlog::error("Unknown particle container type");
                exit(1);
            }
            ljS.simulate(*w, particleContainer);
            break;
        }
        default: {
            show_help();
            return 0;
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "Simulation took: " << duration << "ms" << std::endl;
    auto numIterations = XMLParser::t_end_p / XMLParser::delta_t_p;
    std::cout << "Time per iteration: " << double(duration) / numIterations << "ms" << std::endl;
    return 0;
}

bool parseCommandLineArguments(int argc, char *argsv[]) {
    // variable to remember if flag has already been set
    bool partReset = false;
    /*
     * loop for retrieving command line arguments
     * if program call was faulty help will be printed and program aborted
     * not possible to mix exclusive flags from both simulation types
    */
    for (int i = 1; i < argc; i++) {
        std::string temp = argsv[i];
        if (argc % 2 == 0){
            return false;
        }
        std::string next = argsv[i+1];
        if (temp == "-h") {
            return false;
        } else if (temp == "-input") {
            if (partReset){
                return false;
            }
            inputFile = next;
            i++;
            partReset = true;
        } else {
            // case of unexpected input
            return false;
        }
    }
    return true;
}

void show_help() {
    // prints how to make correct program call
    std::cout << "Please enter a correct program call!" << std::endl;
    std::cout << "\t-h : help page" << std::endl;
    std::cout << "\t-input : path to input xml-file, defaults to ../src/XML_Parser/input.xml" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Example Calls:" << std::endl;
    std::cout << "\t./MolSim" << std::endl;
    std::cout << "\t./MolSim -input ../src/XML_Parser/input.xml" << std::endl;
    std::cout << "Further information in the README." << std::endl;
}
