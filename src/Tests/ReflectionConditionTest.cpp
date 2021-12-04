#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <chrono>
#include <SimulationLogic/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, thresh) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;\
        }

/**
 * @brief Test if the method checkIfSquareRootOfNumberIsBiggerThanCertainValue works properly.
 * For testing this we create several random cutOffs and test the function on random distances.
 */
TEST(Tests, GhostParticlesTest) {
    auto ljS = LennardJonesSimulation();
    ParticleContainerLinkedCells particleContainer(7, 11, 12.5, 3, {0, 0, 0});
    ljS.setParticleContainer(&particleContainer);
    Writer *writer = new XYZWriter();
    ljS.simulate(0.001, 0.001, *writer, 1, "../src/Tests/TestInputFiles/ParamsLJtest.txt",
                 "../src/Tests/TestInputFiles/TestGhostParticlesInput.txt", "GhostParticlesTest");
}

void testIfTwoDoubleArraysAreEqual(const std::array<double, 3> &expected, const std::array<double, 3> &actual,
                                   double threshold) {
    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(expected[i], actual[i], threshold);
    }
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



