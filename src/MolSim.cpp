
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

std::array<double, 3>
calculateFij(double m, double m1, const std::array<double, 3> &array, const std::array<double, 3> &array1);

constexpr double start_time = 0;
constexpr double end_time = 1000;
constexpr double delta_t = 0.014;

// TODO: what data structure to pick?
std::list<Particle> particles;

int main(int argc, char *argsv[]) {

    std::cout << "Hello from MolSim for PSE!" << std::endl;
    if (argc != 2) {
        std::cout << "Erroneous programme call! " << std::endl;
        std::cout << "./molsym filename" << std::endl;
    }

    FileReader fileReader;
    fileReader.readFile(particles, argsv[1]);

    double current_time = start_time;

    int iteration = 0;

    // for this loop, we assume: current x, current f and current v are known
    while (current_time < end_time) {
        // calculate new x
        calculateX();
        // calculate new f
        calculateF();
        // calculate new v
        calculateV();

        iteration++;
        if (iteration % 10 == 0) {
            plotParticles(iteration);
        }
        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    std::cout << "output written. Terminating..." << std::endl;
    return 0;
}

void calculateF() {
    std::list<Particle>::iterator iterator;
    iterator = particles.begin();
    std::array<double, 3> fi;

    for (auto &p1: particles) {
        std::fill(std::begin(fi), std::end(fi), 0);
        for (auto &p2: particles) {
            // @TODO: insert calculation of force here!
            if (!(p1 == p2)) {
                fi = calculateFij(p1.getM(), p2.getM(), p1.getX(), p2.getX());
            }
        }

    }
}

//Wird das Array hier kopiert?
//Warum darf ich mi und mj nicht als reference übergeben?
inline
std::array<double, 3> calculateFij(double mi, double mj, const std::array<double, 3> &xi, const std::array<double, 3> &xj) {
    std::array<double, 3> result;
    double coefficient =
            (mi * mj) / pow(sqrt(pow(xi[0] - xj[0], 2) + pow(xi[1] - xj[1], 2) + pow(xi[2] - xj[2], 2)), 3);
    result[0] = coefficient * (xj[0] - xi[0]);
    result[1] = coefficient * (xj[1] - xi[1]);
    result[2] = coefficient * (xj[2] - xi[2]);
    return result;
}

void calculateX() {
    for (auto &p: particles) {
        // @TODO: insert calculation of force here!

    }
}

void calculateV() {
    for (auto &p: particles) {
        // @TODO: insert calculation of force here!
    }
}

void plotParticles(int iteration) {

    std::string out_name("MD_vtk");

    outputWriter::XYZWriter writer;
    writer.plotParticles(particles, out_name, iteration);
}
