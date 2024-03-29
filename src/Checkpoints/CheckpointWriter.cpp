#include "CheckpointWriter.h"
#include "spdlog/spdlog.h"
#include <fstream>
#include <XML_Parser/BodyBuilder.h>
#include "XML_Parser/XMLParser.h"
#include "SimulationLogic/Simulation.h"

bool CheckpointWriter::writeCheckpointFile(const std::string &fileName, ParticleContainer *particleContainer) {
    std::vector<Particle> particles = particleContainer->getParticles();
    auto filePath = "../Checkpoint_Files/" + fileName;
    std::ofstream outputFile;
    outputFile.open(filePath, std::ios::trunc);

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
                      "#The third line states the number of bodies in the simulation\n"
                      "#The next two lines are the rho/epsilon lookup tables\n"
                      "#\n"
                      "# Molecule data consists of:\n"
                      "# * xyz-coordinates (3 double values)\n"
                      "# * velocities (3 double values)\n"
                      "# * mass (1 double value)\n"
                      "# * type (1 int value)\n"
                      "# * force (3 double values)\n"
                      "# * old force (3 double values)\n"
                      "# * ID (1 int value)\n"
                      "# * partOfMembrane (1 bool value)\n"
                      "# * crossedDomain (3 short values)\n"
                      "#\n"
                      "# xyz-coord\t\tvelocity\t\tmass\t\ttype\t\tforce\t\told force\t\tID\t\tpartOfMembrane\t\tcrossedDomain\n";

        outputFile << std::to_string(particles.size()) + "\n";

        if (XMLParser::calcType_p == Simulation::GRAVITATION) {
            outputFile << "G\n";
        } else {
            outputFile << "LJ\n";
        }
        outputFile << BodyBuilder::toString();
         //if calcType is LJ, toString will automatically add more parameters
        for (auto particle : particles) {
            outputFile << particle.toString() + "\n";
        }
        outputFile.close();
        return true;
    } else {
        spdlog::error("Error: could not open file " + fileName);
        return false;
    }
}
