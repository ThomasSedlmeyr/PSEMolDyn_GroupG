#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <GeometricObjects/Cuboid.h>
#include <chrono>
#include <ParticleContainers/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "OutputWriter/XYZWriter.h"
#include "OutputWriter/VTKWriter.h"
#include "BoundaryConditions//ReflectingCondition.h"

//Code adapted from: https://stackoverflow.com/questions/28768359/comparison-of-floating-point-arrays-using-google-test-and-google-mock
#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, thresh) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;\
        }

/**
 * @brief
 */
TEST(Tests, GhostParticlesTest) {
    ReflectingCondition::isDebug = true;
    auto ljS = LennardJonesSimulation();
    ParticleContainer *particleContainer = new ParticleContainerLinkedCells(7, 11, 12.5, 3, {2, 2, 2, 2, 2, 2});
    Writer *writer = new VTKWriter();
    ljS.simulate(0.001, 0.001, *writer, 1, "../src/Tests/TestInputFiles/ParamsLJtest.txt",
                 "../src/Tests/TestInputFiles/TestGhostParticlesInput.txt", "GhostParticlesTest", particleContainer);
    auto particles = particleContainer->getParticles();

    int counter = 0;
    for (auto & particle : particles) {
        if (particle.getId() == Particle::GHOST_TYPE) {
            counter++;
        }
    }
    EXPECT_EQ(8 + 8 + 11 * 8 + 11, counter);

}

TEST(Tests, TestPointReflection) {
    Cell::sizeX = 3;
    Cell::sizeY = 3.5;
    Cell::sizeZ = 2;
    Cell cell(std::vector<Particle>{}, std::array<double, 3>{4, 4, 4}, Cell::BOUNDARY_CELL);
    std::array<double, 3> pointWhichShouldBeReflected = {5, 5.5, 5.5};
    std::array<double, 3> reflectedPoint{};
    std::array<double, 3> referencePoint{};

    //reflectToRight
    referencePoint = {9, 5.5, 5.5};
    cell.reflectXtoRightCell(pointWhichShouldBeReflected, reflectedPoint);
    EXPECT_FLOATS_NEARLY_EQ(referencePoint, reflectedPoint, 0.0000001);

    //reflectToLeft
    referencePoint = {3, 5.5, 5.5};
    cell.reflectXtoLeftCell(pointWhichShouldBeReflected, reflectedPoint);
    EXPECT_FLOATS_NEARLY_EQ(referencePoint, reflectedPoint, 0.0000001);

    //reflectToTop
    referencePoint = {5, 9.5, 5.5};
    cell.reflectYtoTopCell(pointWhichShouldBeReflected, reflectedPoint);
    EXPECT_FLOATS_NEARLY_EQ(referencePoint, reflectedPoint, 0.0000001);

    //reflectToBottom
    referencePoint = {5, 2.5, 5.5};
    cell.reflectYtoBottomCell(pointWhichShouldBeReflected, reflectedPoint);
    EXPECT_FLOATS_NEARLY_EQ(referencePoint, reflectedPoint, 0.0000001);

    //reflectToFront
    referencePoint = {5, 5.5, 6.5};
    cell.reflectZtoFrontCell(pointWhichShouldBeReflected, reflectedPoint);
    EXPECT_FLOATS_NEARLY_EQ(referencePoint, reflectedPoint, 0.0000001);

    //reflectToBack
    referencePoint = {5, 5.5, 2.5};
    cell.reflectZtoBackCell(pointWhichShouldBeReflected, reflectedPoint);
    EXPECT_FLOATS_NEARLY_EQ(referencePoint, reflectedPoint, 0.0000001);
}



