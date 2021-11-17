//
// Created by thomas on 07.11.21.
//

#include <valarray>
#include <utils/ArrayUtils.h>
#include "GravitationSimulation.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <spdlog/spdlog.h>


GravitationSimulation::GravitationSimulation() = default;
GravitationSimulation::~GravitationSimulation() = default;

std::array<double, 3> GravitationSimulation::calculateFBetweenPair(Particle &p1, Particle &p2) {
    double normalizedDistance{ArrayUtils::L2Norm(p1.getX() - p2.getX())};
    double scalar{p1.getM() * p2.getM() / pow(normalizedDistance, 3)};
    std::array<double, 3> result {scalar * (p2.getX() - p1.getX())};
    return result;
}

//TODO delete?
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

bool GravitationSimulation::readParticles(const std::string &filename) {
    return readFile(particleContainer.getParticles(), filename);
}

bool GravitationSimulation::readFile(std::vector<Particle> &particles, const std::string &fileName) {
    std::array<double, 3> x;
    std::array<double, 3> v;
    double m;
    int num_particles = 0;

    std::ifstream input_file(fileName);
    std::string tmp_string;

    if (input_file.is_open()) {

        getline(input_file, tmp_string);
        spdlog::info("Read line: " + tmp_string);

        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
        }

        std::istringstream numstream(tmp_string);
        numstream >> num_particles;
        spdlog::info("Reading " + std::to_string(num_particles) + ".");
        getline(input_file, tmp_string);
        spdlog::info("Read line: " + tmp_string);

        for (int i = 0; i < num_particles; i++) {
            std::istringstream datastream(tmp_string);

            for (auto &xj: x) {
                datastream >> xj;
            }
            for (auto &vj: v) {
                datastream >> vj;
            }
            if (datastream.eof()) {
                spdlog::error("Error reading file: eof reached unexpectedly reading from line " + std::to_string(i));
                return false;
            }
            datastream >> m;
            particles.emplace_back(x, v, m);

            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
        }
        return true;
    } else {
        spdlog::error("Error: could not open file " + fileName);
        return false;
    }
}

void GravitationSimulation::setParamsWithValues() {
    //The GraviationSimulation does not contain any parameters. This is the reason why this methode ist empty
}

void GravitationSimulation::initializeParamNames() {
    paramNames = {};
}
