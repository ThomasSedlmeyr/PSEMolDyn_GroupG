//
// Created by philip on 01.12.21.
//
#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <GeometricObjects/Cuboid.h>
#include "GeometricObjects/Sphere.h"
#include "utils/ArrayUtils.h"

/**
 * @brief Tests if Cuboid generates the correct number of particles
 */
TEST(GeneratorTests, CuboidGenerationTest) {
    Cuboid cuboid = Cuboid(0, 1, 1);
    std::array<double, 3> structure = {40, 16, 8};
    cuboid.setStructure(structure);
    cuboid.generateParticles(0);
    EXPECT_EQ(cuboid.getParticles().size(), structure[0] * structure[1] * structure[2]);
}

/**
 * @brief Tests for a generated sphere if each point whether it is within the radius
 */
TEST(GeneratorTests, SphereGenerationTest) {
    int numberParticlesPerRadius = 10;
    double meshWidth = 1.0;
    double radiusSize = numberParticlesPerRadius * meshWidth;

    Body *sphere = new Sphere(0, meshWidth, 1, numberParticlesPerRadius);
    Sphere::is2D = false;
    sphere->parsePosition("5,5,5");
    sphere->generateParticles(0);
    std::vector<Particle> particles = sphere->getParticles();

    std::array<double, 3> middlePoint{5, 5, 5};

    for (auto &particle: particles) {
        if (ArrayUtils::L2Norm(middlePoint - particle.getX()) > radiusSize) {
            FAIL();
        }
    }
}

