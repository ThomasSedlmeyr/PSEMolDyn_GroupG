//
// Created by daniel on 15.12.21.
//

#include "CheckpointReader.h"
#include <valarray>
#include <fstream>
#include <spdlog/spdlog.h>
#include "SimulationLogic/Simulation.h"
#include "XML_Parser/BodyBuilder.h"

//ParticleContainer* CheckpointReader::particleContainer;
int CheckpointReader::checkpointReadCalcType;
std::vector<Particle> CheckpointReader::particles;

bool CheckpointReader::readCheckpointFile(const std::string &fileName, ParticleContainer *particleContainer) {
    std::array<double, 3> x = {};
    std::array<double, 3> v = {};
    double m;
    int type;
    std::array<double, 3> f = {};
    std::array<double, 3> old_f = {};
    int id;
    double rho;
    double eps;
    int num_particles = 0;
    std::string temp;
    auto filePath = "../src/Checkpoint_Files/" + fileName;
    std::ifstream input_file(filePath);
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
        //TODO löschen?
        //epsilon and rho lookup table for LJ simulation
        /*
        if (checkpointReadCalcType == Simulation::LENNARDJONES){
            //number of bodies
            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
            BodyBuilder::parseNumberOfBodies(tmp_string);

            //rhoLookupTable
            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
            BodyBuilder::parseRhoLookupTable(tmp_string);

            //epsilonLookupTable
            getline(input_file, tmp_string);
            spdlog::info("Read line: " + tmp_string);
            BodyBuilder::parseEpsilonLookupTable(tmp_string);
        }
         */

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
            datastream >> type;
            for (auto &fj: f) {
                datastream >> fj;
            }
            for (auto &old_fj: old_f) {
                datastream >> old_fj;
            }
            datastream >> id;
            Particle p = Particle(x, v, m, type, f, old_f, id);
            particleContainer->addParticleToContainer(p);
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