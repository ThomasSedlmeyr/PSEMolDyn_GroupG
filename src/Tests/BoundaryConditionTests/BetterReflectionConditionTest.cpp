#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <GeometricObjects/Cuboid.h>
#include <chrono>
#include <ParticleContainers/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "OutputWriter/XYZWriter.h"


//Code adapted from
//https://stackoverflow.com/questions/28768359/comparison-of-floating-point-arrays-using-google-test-and-google-mock
#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, thresh) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;\
        }

/**
 * @brief Creates for each side of the boundary a particle which is located in the halo-area. For each of these particles
 * we than calculate the boundary condition and check the new position and the new velocity.
 */
TEST(Tests, TestReflection) {
    auto ljS = LennardJonesSimulation();
    std::array<int, 6> threes = {3, 3, 3, 3, 3, 3};

    double domainSizeXYZ = 16;
    ParticleContainerLinkedCells particleContainer(domainSizeXYZ, domainSizeXYZ, domainSizeXYZ, 3, threes);
    std::array<double, 3> arrDomainSize = {domainSizeXYZ, domainSizeXYZ, domainSizeXYZ};
    std::unique_ptr<BoundaryConditionContainer> boundaryContainer = std::make_unique<BoundaryConditionContainer>(threes,
                                                                                                                 ParticleContainerLinkedCells::numberCellsX,
                                                                                                                 ParticleContainerLinkedCells::numberCellsY,
                                                                                                                 ParticleContainerLinkedCells::numberCellsZ);
    //In left halo cell
    Particle p1 = Particle({-1.23, 0, 0}, {-10, 2, 1}, 1, -1, 0);
    particleContainer.addParticleToContainer(p1);
    //In right halo cell
    Particle p2 = Particle({domainSizeXYZ + 2, 0, 0}, {4, 2, 1}, 1, -1, 1);
    particleContainer.addParticleToContainer(p2);
    //In top halo cell
    Particle p3 = Particle({3, domainSizeXYZ + 1.7, 0}, {10, 2, 1}, 1, -1, 2);
    particleContainer.addParticleToContainer(p3);
    //In bottom halo cell
    Particle p4 = Particle({0, -1, 0}, {10, -2, 1}, 1, -1, 3);
    particleContainer.addParticleToContainer(p4);
    //In front halo cell
    Particle p5 = Particle({3, 0, domainSizeXYZ + 2}, {10, 2, 1}, 1, -1, 4);
    particleContainer.addParticleToContainer(p5);
    //In back halo cell
    Particle p6 = Particle({1.23, 0, -1.5}, {10, 2, -1}, 1, -1, 5);
    particleContainer.addParticleToContainer(p6);
    //Edge Case:
    //In left and front halo cell
    Particle p7 = Particle({-1.5, 0, domainSizeXYZ + 1.5}, {-10, 2, 1}, 1, -1, 6);
    particleContainer.addParticleToContainer(p7);

    boundaryContainer->calculateBoundaryConditions();
    std::vector<Particle> particles = particleContainer.getParticles();
    sort(particles.begin(), particles.end(), [](const Particle &p1, const Particle &p2) {
        return p1.getId() < p2.getId();
    });

    std::array<std::array<double, 3>, 7> correctPositions = {
            {{1.23, 0, 0}, {domainSizeXYZ - 2, 0, 0}, {3, domainSizeXYZ - 1.7, 0}, {0, 1, 0}, {3, 0, domainSizeXYZ - 2},
             {1.23, 0, 1.5}, {1.5, 0, domainSizeXYZ - 1.5}}};
    std::array<std::array<double, 3>, 7> correctVelocities = {
            {{10, 2, 1}, {-4, 2, 1}, {10, -2, 1}, {10, 2, 1}, {10, 2, -1}, {10, 2, 1}, {10, 2, -1}}};

    for (int i = 0; i < 7; i++) {
        std::cout << i << std::endl;
        EXPECT_FLOATS_NEARLY_EQ(correctPositions[i], particles[i].getX(), 0.0000001);
        EXPECT_FLOATS_NEARLY_EQ(correctVelocities[i], particles[i].getV(), 0.0000001);
    }
}

