//
// Created by philip on 01.12.21.
//

#include <vector>
#include <tuple>
#include <InputReader/XYZReader.h>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <outputWriter/XYZWriter.h>
#include <utils/ArrayUtils.h>
#include <random>
#include "SimulationLogic/LennardJonesSimulation.h"
#include <chrono>

/**
 * @brief Starts a LenardJonesSimulationTest and compares the result of two time steps with two files
 * containing the correct values
 */
TEST(LennardJonesSimulationTests, FullTest) {
    XYZReader reader = XYZReader();
    LennardJonesSimulation gravitationSimulation = LennardJonesSimulation();
    ParticleContainer *particleContainer = new ParticleContainerDirectSum();
    Writer *w = new XYZWriter();
    std::vector<std::array<double, 3>> particles_1_Expected, particles_2_Expected, particles_1_test, particles_2_test;
    try {
        gravitationSimulation.simulate(2, 0.01, *w, 100, "../src/Tests/TestInputFiles/ParamsLJtest.txt",
                                       "../src/Tests/TestInputFiles/TwoCuboidsLJ_Test.txt", "Lenard_Test",
                                       particleContainer);
        particles_1_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/Lenard_Test_0100.xyz");
        particles_2_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/Lenard_Test_0200.xyz");
        particles_1_test= reader.readOnlyPositions("Lenard_Test_0100.xyz");
        particles_2_test = reader.readOnlyPositions("Lenard_Test_0200.xyz");
    }catch(const std::exception& e){
        FAIL();
    }
    for (std::size_t i = 0; i < particles_2_Expected.size(); ++i) {
        EXPECT_NEAR(particles_1_Expected[i][0], particles_1_test[i][0], 0.001);
        EXPECT_NEAR(particles_1_Expected[i][1], particles_1_test[i][1], 0.001);
        EXPECT_NEAR(particles_1_Expected[i][2], particles_1_test[i][2], 0.001);
        EXPECT_NEAR(particles_2_Expected[i][0], particles_2_test[i][0], 0.001);
        EXPECT_NEAR(particles_2_Expected[i][1], particles_2_test[i][1], 0.001);
        EXPECT_NEAR(particles_2_Expected[i][2], particles_2_test[i][2], 0.001);
    }
}

/**
 * @brief reference implementation of Lennard Jones force calculation
 * @param p1
 * @param p2
 * @param epsilon
 * @param rho
 * @return force between p1 and p2
 */
std::array<double, 3> trivialLennardJonesCalculation(Particle &p1, Particle &p2, double epsilon, double rho) {
    double norm = ArrayUtils::L2Norm(p1.getX() - p2.getX());
    double term1 = -24.0*epsilon/pow(norm, 2);
    double term2 =  pow(rho/norm, 6);
    double term3 =  2 * pow(rho/norm, 12);
    return term1 * (term2 - term3) * (p1.getX() - p2.getX());
}

/**
 * @brief Tests the current implementation Lennard Jones force calculation with the reference implementation
 */
TEST(LennardJonesSimulationTests, LennardJonesOptimization){
    int numberOfTries = 100000;

    double epsilon = 5;
    double rho = 1;

    LennardJonesSimulation simulation = LennardJonesSimulation();
    simulation.setEpsilon(epsilon);
    simulation.setRho(rho);

    std::uniform_real_distribution<double> positionDistribution(0, 10);
    std::uniform_real_distribution<double> velocityDistribution(1, 5);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());

    std::array<double, 3> randomPos1{};
    std::array<double, 3> randomPos2{};
    std::array<double, 3> randomVelocity1{};
    std::array<double, 3> randomVelocity2{};

    Particle p1{};
    Particle p2{};

    std::array<double, 3> result1{};
    std::array<double, 3> result2{};

    for (int i = 0; i < numberOfTries; ++i) {
        randomPos1 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};
        randomPos2 = {positionDistribution(re)+11, positionDistribution(re)+11, positionDistribution(re)+11};

        randomVelocity1 = {velocityDistribution(re), velocityDistribution(re), velocityDistribution(re)};
        randomVelocity2 = {velocityDistribution(re), velocityDistribution(re), velocityDistribution(re)};

        p1 = Particle(randomPos1, randomVelocity1, positionDistribution(re), 0, 0);
        p2 = Particle(randomPos2, randomVelocity2, positionDistribution(re), 0, 0);

        //result1 = simulation.calculateFBetweenPair(p1, p2);
        result2 = trivialLennardJonesCalculation(p1, p2, epsilon, rho);

        for (int j = 0; j < 3; ++j) {
            EXPECT_NEAR(result1[j], result2[j], 0.001);
        }
    }
}
