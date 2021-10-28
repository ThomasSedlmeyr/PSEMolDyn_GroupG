
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
calculateFij(double& m, double& m1, const std::array<double, 3> &array, const std::array<double, 3> &array1);

constexpr double start_time = 0;
constexpr double end_time = 1000;
constexpr double delta_t = 0.014;

// TODO: what data structure to pick?
std::vector<Particle> particles;

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
    //std::list<Particle>::iterator iterator;
    //iterator = particles.begin();
    std::vector<std::array<double, 3>> savedFijs(particles.size()-1*(particles.size())/2);
    int currentIndexInSavedFijs = 0;
    int indexForFji;
    for (int i=0; i<particles.size(); i++) {
        std::array<double, 3> fNew{};
        //f1,1
        //f1,2
        //f1,3
        for (int j=0; j<particles.size(); j++) {
            std::array<double, 3> fij{};
            //use the stored Fij
            if(j < i){
                indexForFji = (j*particles.size()+i-(j+1)*(j+2)/2);
                fNew = fNew + -1* savedFijs[indexForFji];
            }
            else if (!(particles[i] == particles[j])) {
                double normalizedDistance = ArrayUtils::L2Norm(particles[i].getX() - particles[j].getX());
                double scalar = particles[i].getM() * particles[j].getM() / pow(normalizedDistance, 3);
                fij = scalar * (particles[j].getX() - particles[i].getX());
                fNew = fNew + fij;
                //save fij if it could later be used
                if(j > i){
                    savedFijs.insert(savedFijs.begin()+currentIndexInSavedFijs, fij);;
                    currentIndexInSavedFijs++;
                }
            }
        }
        particles[i].setF(fNew);
    }
}

bool testOptimizedFormula(){
    //TODO write a test if the optimized formula does the same
    return true;
}

void calculateX() {
    for (auto &p: particles) {
        p.setX(p.getX() + delta_t * p.getV() + pow(delta_t, 2) / (2 * p.getM()) * p.getF());

    }
}

void calculateV() {
    for (auto &p: particles) {
        p.setV(p.getV() + (delta_t / (2 * p.getM())) * (p.getOldF() + p.getF()));
    }
}

void plotParticles(int iteration) {

    std::string out_name("MD_vtk");

    outputWriter::XYZWriter writer;
    writer.plotParticles(particles, out_name, iteration);
}
