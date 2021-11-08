//
// Created by thomas on 07.11.21.
//

#include <valarray>
#include <utils/ArrayUtils.h>
#include <FileReader.h>
#include "GravitationSimulation.h"

void GravitationSimulation::calculateF() {
    calculateFold();
}

GravitationSimulation::GravitationSimulation() {}
GravitationSimulation::~GravitationSimulation() {}

void GravitationSimulation::readInputFile(char *filename){
    FileReader fileReader;
    fileReader.readFile(particleContainer.getParticles(), filename);
    particleContainer.printParticles();
}

void GravitationSimulation::calculateFold() {
    std::vector<std::array<double, 3>> savedFijs(particleContainer.getParticles().size()-1*(particleContainer.getParticles().size())/2);
    int currentIndexInSavedFijs = 0;
    int indexForFji;

    for (std::size_t i=0; i<particleContainer.getParticles().size(); i++) {
        std::array<double, 3> fNew{};

        for (std::size_t j=0; j<particleContainer.getParticles().size(); j++) {
            std::array<double, 3> fij{};
            //use the stored Fij
            if(j < i){
                indexForFji = (j*particleContainer.getParticles().size()+i-(j+1)*(j+2)/2);
                fNew = fNew + -1* savedFijs[indexForFji];
            }
            else if (!(particleContainer.getParticles()[i] == particleContainer.getParticles()[j])) {

                double normalizedDistance = ArrayUtils::L2Norm(particleContainer.getParticles()[i].getX() - particleContainer.getParticles()[j].getX());
                double scalar = particleContainer.getParticles()[i].getM() * particleContainer.getParticles()[j].getM() / pow(normalizedDistance, 3);
                fij = scalar * (particleContainer.getParticles()[j].getX() - particleContainer.getParticles()[i].getX());
                fNew = fNew + fij;
                //save fij if it could later be used
                if(j > i){
                    savedFijs.insert(savedFijs.begin()+currentIndexInSavedFijs, fij);
                    currentIndexInSavedFijs++;
                }
            }
        }
        //Rausfinden
        particleContainer.getParticles()[i].setOldF(particleContainer.getParticles()[i].getF());
        particleContainer.getParticles()[i].setF(fNew);
    }
}

void GravitationSimulation::calculateFslower() {
    for (auto &p1 : particleContainer.getParticles()) {
        std::array<double, 3> fNew{};
        for (auto &p2 : particleContainer.getParticles()) {
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
