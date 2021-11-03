/**
 * @brief Main class for Simulation
 */
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"
#include "ParticleContainer.h"

#include <iostream>
#include <list>
#include <outputWriter/VTKWriter.h>

/**
 * @brief shows guidelines for correct program calls
 */
void show_help();

constexpr double start_time = 0;

/**
 * @brief public variable for end of calculation
 *
 * not const because of optional passing of arguments through command line
 */
double end_time = 1000;

/**
 * @brief public variable for stepsize of calculation
 *
 * not const because of optional passing of arguments through command line
 */
double delta_t = 0.014;

// TODO: what data structure to pick?
std::vector<Particle> particles;

int main(int argc, char *argsv[]) {

    std::cout << "Hello from MolSim for PSE!" << std::endl;
    if (argc < 2 || argc > 6 || argc % 2 == 1) { // cases in which correct programme call is not possible
        std::cout << "Erroneous programme call! " << std::endl;
        std::cout << "./molsym filename" << std::endl;
        show_help();
        return 0;
    }

    // parsing of potential parameters t_end or delta_t
    // prints help in case of wrong call
    bool endReset = false;
    bool deltaReset = false;
    bool runTest = false;
    for (int i = 2; i < argc; i++) {
        std::string temp = argsv[i];
        std::string next = argsv[i+1];
        if (temp == "-h") {
            show_help();
            return 0;
        } else if (temp == "-t_end") {
            if (endReset || next == "-t_end" || next == "-delta_t" || strtod(next.c_str(), nullptr) <= 0){
                show_help();
                return 0;
            }
            temp = argsv[++i];
            end_time = strtod(temp.c_str(), nullptr);
            endReset = true;
        } else if (temp == "-delta_t") {
            if (deltaReset || next == "-t_end" || next == "-delta_t" || strtod(next.c_str(), nullptr) <= 0){
                show_help();
                return 0;
            }
            temp = argsv[++i];
            delta_t = atof(temp.c_str());
            deltaReset = true;
        } else {
            show_help();
            return 0;
        }
    }

    FileReader fileReader;
    fileReader.readFile(particleContainer.getParticles(), argsv[1]);

    if (runTest){
        bool success = particleContainer.testOptimizedFormula();
        if(success){
            std::cout << "No errors in fast force calculation\n";
        }else{
            std::cout << "Errors in fast force calculation\n";
        }
        return 0;
    }
    double current_time = start_time;

    int iteration = 0;
    // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {
        // calculate new x
        particleContainer.calculateX(delta_t);
        // calculate new f
        particleContainer.calculateF();
        // calculate new v
        particleContainer.calculateV(delta_t);

        iteration++;
        if (iteration % 10 == 0) {
            particleContainer.plotParticles(iteration);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return 0;
}

void show_help() {
    // prints how to make correct programme call
    std::cout << "Please enter e correct programme call!" << std::endl;
    std::cout << "-h : help page " << std::endl;
    std::cout << "-t_end : end value, defaults to 1000" << std::endl;
    std::cout << "-delta_t : stepsize, defaults to 0.014" << std::endl;
    std::cout << "Example : ./MolSim ../eingabe-sonne.txt -t_end 1000 -delta_t 0.014" << std::endl;
}
