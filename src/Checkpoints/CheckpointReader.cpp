//
// Created by daniel on 15.12.21.
//

#include "CheckpointReader.h"
#include <valarray>
#include <fstream>
#include <spdlog/spdlog.h>
#include "SimulationLogic/Simulation.h"

//ParticleContainer* CheckpointReader::particleContainer;
int CheckpointReader::checkpointReadCalcType;
std::vector<Particle> CheckpointReader::particles;

bool CheckpointReader::readCheckpointFile(const std::string &fileName) {
    std::array<double, 3> x = {};
    std::array<double, 3> v = {};
    double m;
    double rho;
    double eps;
    int num_particles = 0;
    std::string temp;

    std::ifstream input_file(fileName);
    std::string tmp_string;

    if (input_file.is_open()) {

        getline(input_file, tmp_string);
        spdlog::info("Read line: " + tmp_string);

        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
        }

        // number of particles
        std::istringstream numstream(tmp_string);
        numstream >> num_particles;
        spdlog::info("Reading " + std::to_string(num_particles) + ".");
        getline(input_file, tmp_string);
        spdlog::info("Read line: " + tmp_string);

        // calculation type
       temp = tmp_string;
        if (temp == "G") {
            CheckpointReader::checkpointReadCalcType = Simulation::GRAVITATION;
        } else if (temp == "LJ") {
            CheckpointReader::checkpointReadCalcType = Simulation::LENNARDJONES;
        } else {
            spdlog::error("Error reading file: Unknown calculation type.");
            return false;
        }

        for (int i = 0; i < num_particles; i++) {
            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
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
            if (CheckpointReader::checkpointReadCalcType == Simulation::LENNARDJONES) {
                datastream >> rho; // TODO
                datastream >> eps; // TODO
            }
            Particle p = Particle(x, v, m);
            // particleContainer->addParticleToContainer(p);
            particles.push_back(p);

            //getline(input_file, tmp_string);
            //spdlog::info("Read line: " + tmp_string);
        }
        return true;
    } else {
        spdlog::error("Error: could not open file " + fileName);
        return false;
    }
}