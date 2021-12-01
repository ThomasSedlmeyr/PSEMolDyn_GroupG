//
// Created by philip on 01.12.21.
//
#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>

/**
 * @brief Tests if Cuboid generates the correct number of particles
 */
TEST(GeneratorTests, CuboidGenerationTest){
    Cuboid cuboid = Cuboid(0, 1, 1);
    std::array<double, 3> structure = {40, 16, 8};
    cuboid.setStructure(structure);
    cuboid.generateParticles(0);
    EXPECT_EQ(cuboid.getParticles().size(), structure[0]*structure[1]*structure[2]);
}

