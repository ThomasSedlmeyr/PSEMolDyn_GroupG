#include <vector>
#include <gtest/gtest.h>
#include "Checkpoints/CheckpointReader.h"
#include "SimulationLogic/Simulation.h"
#include "ParticleContainers/ParticleContainer.h"

/**
 * @brief quick test for reading checkpoint as input
 */
TEST(InputTests, ReadCheckpoints) {
    std::string filename = "../src/Checkpoint_Files/checkpoints_G_example.txt";
    bool success = CheckpointReader::readCheckpointFile(filename);

    std::vector<Particle> parts = CheckpointReader::particleContainer->getParticles();
    EXPECT_EQ(parts.size(), 4);
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 9.55e-4);
    parts.pop_back();
    EXPECT_DOUBLE_EQ(parts.back().getM(), 3.0e-6);
}