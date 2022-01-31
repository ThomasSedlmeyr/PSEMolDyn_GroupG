#include <gtest/gtest.h>
#include <random>
#include <ParticleContainers/ParticleContainerLinkedCells.h>
#include <chrono>
#include <OutputWriter/Writer.h>
#include <SimulationLogic/LennardJonesSimulation.h>
#include <OutputWriter/VTKWriter.h>
#include <OutputWriter/XYZWriter.h>
#include <InputReader/XYZReader.h>
#include "omp.h"

/**
 * @TODO Philip
 */
void generateReference(){
    XMLParser::parseXML("../src/Tests/TestInputFiles/RayleighTaylorTest.xml");
    XMLParser::parallelType_p = Simulation::NOTPARALLEL;
    std::array<int, 6> reflectingConditions = {3,3,3,3,3,3};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(100, 100, 100, 3.0, reflectingConditions);
    Writer *w = new XYZWriter();
    LennardJonesSimulation s1 = LennardJonesSimulation();
    s1.simulate(*w, &particleContainerLinkedCells);
}

/**
 * @brief tests if the FIRSTPARALLEL-implementation generates the same result as the
 * sequential implementation
 */
TEST(ParallelAlgorithmsTests, TestBasicParallelizationFirstParallel) {
    XMLParser::parallelType_p = Simulation::FIRSTPARALLEL;
    XMLParser::parseXML("../src/Tests/TestInputFiles/RayleighTaylorTest.xml");
    omp_set_num_threads(12);
    std::array<int, 6> reflectingConditions = {3,3,3,3,3,3};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(100, 100, 100, 3.0, reflectingConditions);
    Writer *w = new XYZWriter();
    LennardJonesSimulation s1 = LennardJonesSimulation();
    s1.simulate(*w, &particleContainerLinkedCells);

    XYZReader reader = XYZReader();
    std::vector<std::array<double, 3>> particlesSequential, particlesParallel;

    particlesSequential = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/RayleighTaylorTest_0100.xyz");
    particlesParallel = reader.readOnlyPositions("RayleighTaylorTest_0100.xyz");
    for (std::size_t i = 0; i < particlesParallel.size(); ++i) {
        EXPECT_NEAR(particlesSequential[i][0], particlesParallel[i][0], 0.01);
        EXPECT_NEAR(particlesSequential[i][1], particlesParallel[i][1], 0.01);
        EXPECT_NEAR(particlesSequential[i][2], particlesParallel[i][2], 0.01);
    }
}

/**
 * @brief tests if the SECONDPARALLEL-implementation generates the same result as the
 * sequential implementation
 */
TEST(ParallelAlgorithmsTests, TestBasicParallelizationSecondParallel) {
    XMLParser::parallelType_p = Simulation::SECONDPARALLEL;
    XMLParser::parseXML("../src/Tests/TestInputFiles/RayleighTaylorTest.xml");
    omp_set_num_threads(12);
    std::array<int, 6> reflectingConditions = {3,3,3,3,3,3};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(100, 100, 100, 3.0, reflectingConditions);
    Writer *w = new XYZWriter();
    LennardJonesSimulation s1 = LennardJonesSimulation();
    s1.simulate(*w, &particleContainerLinkedCells);

    XYZReader reader = XYZReader();
    std::vector<std::array<double, 3>> particlesSequential, particlesParallel;

    particlesSequential = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/RayleighTaylorTest_0100.xyz");
    particlesParallel = reader.readOnlyPositions("RayleighTaylorTest_0100.xyz");
    for (std::size_t i = 0; i < particlesParallel.size(); ++i) {
        EXPECT_NEAR(particlesSequential[i][0], particlesParallel[i][0], 0.01);
        EXPECT_NEAR(particlesSequential[i][1], particlesParallel[i][1], 0.01);
        EXPECT_NEAR(particlesSequential[i][2], particlesParallel[i][2], 0.01);
    }
}
