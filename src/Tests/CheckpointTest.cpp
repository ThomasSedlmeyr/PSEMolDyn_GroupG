#include <vector>
#include <gtest/gtest.h>
#include "Checkpoints/CheckpointReader.h"
#include "SimulationLogic/Simulation.h"
#include "ParticleContainers/ParticleContainer.h"
#include "Checkpoints/CheckpointWriter.h"
#include "XML_Parser/XMLParser.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "2D/ParticleContainerLinkedCells2D.h"
#include "OutputWriter/VTKWriter.h"

const int Simulation::LENNARDJONES;
const int Simulation::GRAVITATION;

/**
 * @brief quick test for reading checkpoint as input
 */
TEST(InputTests, ReadGCheckpoints) {
    std::string filename = "checkpoints_G_example.txt";
    bool success = CheckpointReader::readCheckpointFile(filename, new ParticleContainerDirectSum());
    EXPECT_EQ(success, true);

    //std::vector<Particle> parts = CheckpointReader::particleContainer->getParticles();
    std::vector<Particle> parts = CheckpointReader::particles;

    EXPECT_EQ(parts.size(), 4);
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 9.55e-4);
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 3.0e-6);
}

/**
 * @brief test for writing checkpoints
 */
TEST(OutputTests, WriteGCheckpoints) {
    bool xmlSuccess = XMLParser::parseXML("../src/Tests/TestInputFiles/input_test.xml");
    EXPECT_EQ(xmlSuccess, true);

    ParticleContainer *particleContainer = new ParticleContainerDirectSum();
    Particle a = Particle({0, 0, 0}, {0, 0, 0}, 5, 2, {0, 0, 0}, {0, 0, 0}, 7);
    Particle b = Particle({1, 0, 0}, {0, 0, 0}, 564.7777, 2, {0, 0, 0}, {0, 0, 0}, 9);
    Particle c = Particle({0, 1, 0}, {0, 0, 0}, 23, 2, {0, 0, 0}, {0, 0, 0}, 74);
    particleContainer->addParticleToContainer(a);
    particleContainer->addParticleToContainer(b);
    particleContainer->addParticleToContainer(c);

    bool success = CheckpointWriter::writeCheckpointFile("checkpoint_G_writeExample2.txt", particleContainer);
    EXPECT_EQ(success, true);

    bool successReader = CheckpointReader::readCheckpointFile("checkpoint_G_writeExample2.txt", new ParticleContainerDirectSum());
    EXPECT_EQ(successReader, true);

    EXPECT_EQ(CheckpointReader::checkpointReadCalcType, Simulation::LENNARDJONES);

    std::vector<Particle> parts = CheckpointReader::particles;
    EXPECT_EQ(parts.size(), 3);
    EXPECT_DOUBLE_EQ(parts.back().getM(), 23);
    parts.pop_back();
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 5);
    EXPECT_EQ(parts.back().getId(), 7);
}

/**
 * @brief sorts two particles by ID
 * @param p1
 * @param p2
 * @return first parameters id is smaller
 */
bool sortHelper(Particle &p1, Particle &p2){
    return p1.getId() < p2.getId();
}

/**
 * @brief test to compare regular simulation with one that is saved into checkpoints and resumed afterwards
 */
TEST(InOutTests, ReadWriteCheckpoints) {

    //
    bool xmlSuccess1 = XMLParser::parseXML("../src/Tests/TestInputFiles/CheckpointReadWriteTest_1.xml");
    EXPECT_EQ(xmlSuccess1, true);

    LennardJonesSimulation lj = LennardJonesSimulation();
    Writer *w = new VTKWriter();
    std::array<int, 4> boundaryConditions = {XMLParser::right_p, XMLParser::left_p, XMLParser::top_p, XMLParser::bottom_p};
    //ParticleContainer *particleContainer = new twoD::ParticleContainerLinkedCells2D(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::cutoffRadius, boundaryConditions);
    ParticleContainer* particleContainer = new ParticleContainerLinkedCells(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::domainSize[2], XMLParser::cutoffRadius, XMLParser::boundaryConditions);
    lj.simulate(*w, particleContainer);

    //
    XMLParser::resetInternalData();
    bool xmlSuccess2 = XMLParser::parseXML("../src/Tests/TestInputFiles/CheckpointReadWriteTest_2.xml");
    EXPECT_EQ(xmlSuccess2, true);
    LennardJonesSimulation lj2 = LennardJonesSimulation();
    Writer *w2 = new VTKWriter();
    std::array<int, 4> boundaryConditions2 = {XMLParser::right_p, XMLParser::left_p, XMLParser::top_p, XMLParser::bottom_p};
    //ParticleContainer *particleContainer2 = new twoD::ParticleContainerLinkedCells2D(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::cutoffRadius, boundaryConditions);
    ParticleContainer* particleContainer2 = new ParticleContainerLinkedCells(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::domainSize[2], XMLParser::cutoffRadius, XMLParser::boundaryConditions);
    lj2.simulate(*w2, particleContainer2);
    std::vector<Particle> particles_1 = particleContainer2->getParticles();

    //
    XMLParser::resetInternalData();
    bool xmlSuccess3 = XMLParser::parseXML("../src/Tests/TestInputFiles/CheckpointReadWriteTest_3.xml");
    EXPECT_EQ(xmlSuccess3, true);
    LennardJonesSimulation lj3 = LennardJonesSimulation();
    Writer *w3 = new VTKWriter();
    std::array<int, 4> boundaryConditions3 = {XMLParser::right_p, XMLParser::left_p, XMLParser::top_p, XMLParser::bottom_p};
    //ParticleContainer *particleContainer3 = new twoD::ParticleContainerLinkedCells2D(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::cutoffRadius, boundaryConditions);
    ParticleContainer* particleContainer3 = new ParticleContainerLinkedCells(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::domainSize[2], XMLParser::cutoffRadius, XMLParser::boundaryConditions);
    lj2.simulate(*w3, particleContainer3);
    std::vector<Particle> particles_2 = particleContainer3->getParticles();

    //
    std::sort(particles_1.begin(), particles_1.end(), sortHelper);
    std::sort(particles_2.begin(), particles_2.end(), sortHelper);
    for (int i = 0; i < particles_2.size(); ++i) {
        std::cout << "particle: " << i << std::endl;
        EXPECT_EQ(particles_1[i].getId(), particles_2[i].getId());
        for (int j = 0; j < 2; ++j) {
            EXPECT_NEAR(particles_1[i].getX()[j], particles_2[i].getX()[j], 0.005);
        }
    }
}