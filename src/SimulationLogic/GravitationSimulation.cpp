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
#include <Visitors/GravForceVisitor.h>

GravitationSimulation::GravitationSimulation() = default;

GravitationSimulation::~GravitationSimulation() = default;

bool GravitationSimulation::readParticles(const std::string &filename) {
    return readFile(filename);
}

bool GravitationSimulation::readFile(const std::string &fileName) {
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
            Particle p = Particle(x, v, m);
            particleContainer->addParticleToContainer(p);

            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
        }
        return true;
    } else {
        spdlog::error("Error: could not open file " + fileName);
        return false;
    }
}

void GravitationSimulation::calculateF() {
    particleContainer->walkOverParticlePairs(forceCalcVisitor);

}
