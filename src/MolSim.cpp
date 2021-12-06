/**
 * @file MolSim.cpp
 * @brief Main class for Simulation
 */

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
int calcType = Simulation::LENNARDJONES;

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
    Writer *w = new VTKWriter();
    switch (calcType) {
        case Simulation::GRAVITATION: {
            auto gS = GravitationSimulation();
            ParticleContainer *particleContainer = new ParticleContainerDirectSum();
            gS.simulate(end_time, delta_t, *w, 10, "", gravitation_path, "Grav", particleContainer);
            break;
        }
        case Simulation::LENNARDJONES: {
            auto ljS = LennardJonesSimulation();
            ParticleContainer *particleContainer = new ParticleContainerLinkedCells(70, 40, 6, 3, {3, 3, 3, 3, 3, 3});
            ljS.simulate(end_time, delta_t, *w, 10, param_pathLJ, particles_pathLJ, "Lenard", particleContainer);
            break;
        }
        default: {
            show_help();
            return 0;
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Simulation took: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;

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
        }
        if (temp == "-t_end") {
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
            if (inputReset || (calcReset && calcType == Simulation::LENNARDJONES) || paramReset || partReset || next == "-t_end"
                || next == "-delta_t" || next == "-calcType" || next == "-input"|| next == "-param_path"
                || next == "-particles_path") {
                return false;
            }
            gravitation_path = next;
            i++;
            inputReset = true;
        } else if (temp == "-param_path") {
            if (paramReset || (calcReset && calcType == Simulation::GRAVITATION) || inputReset || next == "-t_end" || next == "-delta_t"
                || next == "-calcType" || next == "-input"|| next == "-param_path" || next == "-particles_path") {
                return false;
            }
            param_pathLJ = next;
            i++;
            paramReset = true;
        } else if (temp == "-particles_path") {
            if (partReset || (calcReset && calcType == Simulation::GRAVITATION) || inputReset || next == "-t_end" || next == "-delta_t"
                || next == "-calcType" || next == "-input"|| next == "-param_path" || next == "-particles_path") {
                return false;
            }
            particles_pathLJ = next;
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
    std::cout << "\t-h : help page " << std::endl;
    std::cout << "\t-t_end : end value, defaults to 5" << std::endl;
    std::cout << "\t-delta_t : stepsize, defaults to 0.0002" << std::endl;
    std::cout << "\t-calcType : 1 for Gravitation Simulation, 2 for 'Collision of two bodies', defaults to 2 " << std::endl;
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
