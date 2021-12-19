#include <vector>
#include <gtest/gtest.h>
#include "Checkpoints/CheckpointReader.h"
#include "SimulationLogic/Simulation.h"
#include "ParticleContainers/ParticleContainer.h"
#include "Checkpoints/CheckpointWriter.h"
#include "XML_Parser/XMLParser.h"

/**
 * @brief quick test for reading checkpoint as input
 */
TEST(InputTests, ReadGCheckpoints) {
    std::string filename = "../src/Checkpoint_Files/checkpoints_G_example.txt";
    bool success = CheckpointReader::readCheckpointFile(filename);
    EXPECT_EQ(success, true);

    //std::vector<Particle> parts = CheckpointReader::particleContainer->getParticles();
    std::vector<Particle> parts = CheckpointReader::particles;

    EXPECT_EQ(parts.size(), 4);
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 9.55e-4);
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 3.0e-6);
}

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

    bool success = CheckpointWriter::writeCheckpointFile("../src/Checkpoint_Files/checkpoint_G_writeExample.txt", particleContainer);
    EXPECT_EQ(success, true);

    bool successReader = CheckpointReader::readCheckpointFile("../src/Checkpoint_Files/checkpoint_G_writeExample.txt");
    EXPECT_EQ(successReader, true);

    std::vector<Particle> parts = CheckpointReader::particles;
    EXPECT_EQ(parts.size(), 3);
    EXPECT_DOUBLE_EQ(parts.back().getM(), 23);
    parts.pop_back();
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 5);
    EXPECT_EQ(parts.back().getId(), 7);
}