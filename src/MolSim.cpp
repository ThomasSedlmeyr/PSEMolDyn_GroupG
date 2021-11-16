/**
 * @file MolSim.cpp
 * @brief Main class for Simulation
 */

#include "SimulationLogic/ParticleContainer.h"
#include "SimulationLogic/GravitationSimulation.h"
#include "outputWriter/Writer.h"

#include <iostream>
#include <outputWriter/VTKWriter.h>
#include <outputWriter/XYZWriter.h>
#include <SimulationLogic/LennardJonesSimulation.h>
#include <spdlog/spdlog.h>

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

constexpr double start_time = 0;

/**
 * @brief public variable for end of calculation
 *
 * not const because of optional passing of arguments through command line
 */
double end_time = 5;

/**
 * @brief public variable for stepsize of calculation
 *
 * not const because of optional passing of arguments through command line
 */
double delta_t = 0.0002;

/**
 * @brief public variable defining calculation method
 *
 * 1 for GravitationSimulation
 * 2 for LennardJonesSimulation (default)
 */
int calcType = 2;

/**
 * @brief path to file for parameters for Lennard Jones Simulation
 */
std::string param_pathLJ = "../ParamsLennardJonesSimulation.txt";

/**
 * @brief path to file for particles for Lennard Jones Simulation
 */
std::string particles_pathLJ = "../TwoCuboidsLJ.txt";

/**
 * @brief path to input file
 */
std::string gravitation_path = "../eingabe-sonne.txt";

ParticleContainer particleContainer;

int main(int argc, char *argsv[]) {
    spdlog::info("Logger Test");
    std::cout << "Hello from MolSim for PSE!" << std::endl;

    // cases in which correct programme call is not possible
    if (argc < 1) {
        std::cout << "Erroneous programme call! " << std::endl;
        show_help();
        return 0;
    }

    // parsing of potential parameters t_end or delta_t
    bool success = parseCommandLineArguments(argc, argsv);
    // prints help in case of wrong call
    if (!success) {
        show_help();
        return 0;
    }

    //bool runTest = false;
    //test won't get executed unless runTest boolean is set to true
    /*if (runTest){
        bool success = particleContainer.testOptimizedFormula();
        if(success){
            std::cout << "No errors in fast force calculation\n";
        }else{
            std::cout << "Errors in fast force calculation\n";
        }
        return 0;
    }*/
    //double current_time = start_time;

    Writer *w = new VTKWriter();
    switch (calcType) {
        case 1: {
            auto gS = GravitationSimulation();
            gS.simulate(end_time, delta_t, *w, 10, "", gravitation_path, "Grav");
            break;
        }
        case 2: {

            auto ljS = LennardJonesSimulation();
            ljS.simulate(end_time, delta_t, *w, 10, param_pathLJ, particles_pathLJ, "Lenard");
            break;
        }
        default: {
            show_help();
            return 0;
        }
    }

    return 0;
}

bool parseCommandLineArguments(int argc, char *argsv[]) {
    // variable to remember if flag has already been set
    bool endReset = false;
    bool deltaReset = false;
    bool calcReset = false;
    bool inputReset = false;
    bool paramReset = false;
    bool partReset = false;

    for (int i = 1; i < argc; i++) {
        std::string temp = argsv[i];
        std::string next = argsv[i+1];
        if (temp == "-h") {
            return false;
        } else if (temp == "-t_end") {
            if (endReset || strtod(next.c_str(), nullptr) <= 0 || next == "-t_end" || next == "-delta_t"
                || next == "-calcType" || next == "-input"|| next == "-param_path" || next == "-particles_path") {
                return false;
            }
            end_time = strtod(next.c_str(), nullptr);
            i++;
            endReset = true;
        } else if (temp == "-delta_t") {
            if (deltaReset || strtod(next.c_str(), nullptr) <= 0 || next == "-t_end" || next == "-delta_t"
                || next == "-calcType" || next == "-input"|| next == "-param_path" || next == "-particles_path") {
                return false;
            }
            delta_t = strtod(next.c_str(), nullptr);
            i++;
            deltaReset = true;
        } else if (temp == "-calcType") {
            if (calcReset || strtod(next.c_str(), nullptr) <= 0 || strtod(next.c_str(), nullptr) > 2
                || next == "-t_end" || next == "-delta_t" || next == "-calcType" || next == "-input"
                || next == "-param_path" || next == "-particles_path") {
                return false;
            }
            calcType = strtod(next.c_str(), nullptr);
            i++;
            calcReset = true;
        } else if (temp == "-input") {
            if (inputReset || (calcReset && calcType == 2) || paramReset || partReset || next == "-t_end"
                || next == "-delta_t" || next == "-calcType" || next == "-input"|| next == "-param_path"
                || next == "-particles_path") {
                return false;
            }
            gravitation_path = next;
            i++;
            inputReset = true;
        } else if (temp == "-param_path") {
            if (paramReset || (calcReset && calcType == 1) || inputReset || next == "-t_end" || next == "-delta_t"
                || next == "-calcType" || next == "-input"|| next == "-param_path" || next == "-particles_path") {
                return false;
            }
            param_pathLJ = next;
            i++;
            paramReset = true;
        } else if (temp == "-particles_path") {
            if (partReset || (calcReset && calcType == 1) || inputReset || next == "-t_end" || next == "-delta_t"
                || next == "-calcType" || next == "-input"|| next == "-param_path" || next == "-particles_path") {
                return false;
            }
            particles_pathLJ = next;
            i++;
            partReset = true;
        } else {
            return false;
        }
    }
    return true;
}

void show_help() {
    // prints how to make correct program call
    std::cout << "Please enter a correct program call!" << std::endl;
    std::cout << "\t-h : help page " << std::endl;
    std::cout << "\t-t_end : end value, defaults to 5" << std::endl;
    std::cout << "\t-delta_t : stepsize, defaults to 0.0002" << std::endl;
    std::cout << "\t-calcType : 1 for Gravitation Simulation, 2 for Lennard Jones Simulation, defaults to 2 " << std::endl;
    std::cout << "Only for Gravitation Simulation:" << std::endl;
    std::cout << "\t-input : path to input file, defaults to ../eingabe-sonne.txt" << std::endl;
    std::cout << "Only for Lennard Jones Simulation:" << std::endl;
    std::cout << "\t-param_path : path to input file for parameters, defaults to ../ParamsLennardJonesSimulation.txt" << std::endl;
    std::cout << "\t-particles_path : path to input file for particles, defaults to ../TwoCuboidsLJ.txt" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Example for Gravitation Simulation:" << std::endl;
    std::cout << "\t./MolSim -calcType 1 -input ../eingabe-sonne.txt -t_end 1000 -delta_t 0.014" << std::endl;
    std::cout << "Example for Lennard Jones Simulation:" << std::endl;
    std::cout << "\t./MolSim -calcType 2 -param_path ../ParamsLennardJonesSimulation.txt -particles_path ../TwoCuboidsLJ.txt -t_end 5 -delta_t 0.0002" << std::endl;
    std::cout << "Further information in the README." << std::endl;
}
