#include <outputWriter/VTKWriter.h>
#include <utils/ArrayUtils.h>
#include <iostream>
#include "ParticleContainer.h"

std::vector<Particle> &ParticleContainer::getParticles() {
    return particles;
}

void ParticleContainer::plotParticles(int &iteration) {
    std::string out_name("MD_vtk");
    outputWriter::VTKWriter writer;

    writer.initializeOutput(particles.size());
    for (Particle &particle : particles) {
        writer.plotParticle(particle);
    }
    writer.writeFile(out_name, iteration);
}

void ParticleContainer::calculateX(const double &delta_t) {
    for (auto &p: particles) {
        p.setX(p.getX() + delta_t * p.getV() + pow(delta_t, 2) / (2 * p.getM()) * p.getF());
    }
}

void ParticleContainer::calculateV(const double &delta_t) {
    for (auto &p: particles) {
        p.setV(p.getV() + (delta_t / (2 * p.getM())) * (p.getOldF() + p.getF()));
    }
}

/**
 * @brief calculates the force for every particle
 */
void ParticleContainer::calculateF() {
    std::vector<std::array<double, 3>> savedFijs(particles.size()-1*(particles.size())/2);
    int currentIndexInSavedFijs = 0;
    int indexForFji;

    for (int i=0; i<particles.size(); i++) {
        std::array<double, 3> fNew{};

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
                    savedFijs.insert(savedFijs.begin()+currentIndexInSavedFijs, fij);
                    currentIndexInSavedFijs++;
                }
            }
        }
        particles[i].setOldF(particles[i].getF());
        particles[i].setF(fNew);
    }
}

/**
 * @brief calculates the force for every particle in an easy but inefficient way
 */
void ParticleContainer::calculateFslower() {
    for (auto &p1 : particles) {
        std::array<double, 3> fNew{};
        for (auto &p2 : particles) {
            if (!(p1 == p2)) {
                double normalizedDistance{ArrayUtils::L2Norm(p1.getX() - p2.getX())};
                double scalar{p1.getM() * p2.getM() / pow(normalizedDistance, 3)};
                fNew = fNew + scalar * (p2.getX() - p1.getX());
            }
        }
        p1.setOldF(p1.getF());
        p1.setF(fNew);
    }
}
bool ParticleContainer::testOptimizedFormula(){
    bool isCorrect = true;
    for (int i = 0; i < 1000; ++i) {
        //Store the original configuration
        std::vector<Particle> particlesOriginal = particles;
        //calculate the new force on particles with optimized Method
        calculateF();
        //store result for comparison with slower implementation
        std::vector<Particle> resultFast = particles;
        //reset particles to original state
        particles = particlesOriginal;
        calculateFslower();
        //Now compare particles with resultFast
        for (int j = 0; j < particles.size(); ++j) {
            if (!(particles[j] == resultFast[j])) {
                std::cout << "Error in Fast Calculation\n";
                isCorrect = false;
            }
        }
        calculateX(0.014);
        calculateV(0.014);
    }
    return isCorrect;
}
