
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

void show_help();

constexpr double start_time = 0;
double end_time = 1000; // not const because of possible parameter over console
double delta_t = 0.014; // not const because of possible parameter over console

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

    // parse potential parameters t_end or delta_t or print help
    bool endReset = false;
    bool deltaReset = false;
    for (int i = 2; i < argc; i++) {
        std::string temp = argsv[i];
        std::string next = argsv[i+1];
        if (temp == "-h") {
            show_help();
            return 0;
        } else if (temp == "-t_end") {
            if (endReset || next == "-t_end" || next == "-delta_t" || atof(next.c_str()) <= 0){
                show_help();
                return 0;
            }
            temp = argsv[++i];
            end_time = atof(temp.c_str());
            endReset = true;
        } else if (temp == "-delta_t") {
            if (deltaReset || next == "-t_end" || next == "-delta_t" || atof(next.c_str()) <= 0){
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

void show_help() {
    // prints how to make correct programme call
    std::cout << "Please enter e correct programme call!" << std::endl;
    std::cout << "-h : help page " << std::endl;
    std::cout << "-t_end : end value, defaults to 1000" << std::endl;
    std::cout << "-delta_t : stepsize, defaults to 0.014" << std::endl;
    std::cout << "Exemple : ./molsym ../eingabe-sonne.txt -t_end 1000 -delta_t 0.014" << std::endl;
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
