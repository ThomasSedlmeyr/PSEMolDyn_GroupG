#include "CheckpointWriter.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include "XML_Parser/XMLParser.h"
#include "SimulationLogic/Simulation.h"

bool CheckpointWriter::writeCheckpointFile(const std::string &fileName, ParticleContainer *particleContainer) {
    std::vector<Particle> particles = particleContainer->getParticles();

    std::ofstream outputFile;
    outputFile.open(fileName, std::ios::trunc);

    if (outputFile.is_open()) {
        outputFile << "#\n"
                      "# file format:\n"
                      "# Lines of comment start with '#' and are only allowed at the beginning of the file\n"
                      "# Empty lines are not allowed.\n"
                      "# The first line not being a comment has to be one integer, indicating the number of\n"
                      "# molecule data sets.\n"
                      "#\n"
                      "# The second line not being a comment has to either be G or LJ indicating whether the\n"
                      "# particles were saved from a Gravitation Simulation or Lennard Jones Simulation.\n"
                      "#\n"
                      "# Molecule data consists of:\n"
                      "# * xyz-coordinates (3 double values)\n"
                      "# * velocities (2 or 3 double values)\n"
                      "# * mass (1 double value)\n"
                      "# For LJ also:\n"
                      "# * rho (1 double value)\n"
                      "# * epsilon (1 double value)\n"
                      "#\n"
                      "# xyz-coord      velocity        mass\n";
        outputFile << std::to_string(particles.size()) + "\n";

        if (XMLParser::calcType_p == Simulation::GRAVITATION) {
            outputFile << "G\n";
        } else {
            outputFile << "LJ\n";
        }

        for (auto particle : particles) {
            outputFile << particle.toString() + "\n";
        }
        return true;
    } else {
        spdlog::error("Error: could not open file " + fileName);
        return false;
    }
}
