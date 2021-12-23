//
// Created by philip on 01.12.21.
//

#include <vector>
#include <tuple>
#include <InputReader/XYZReader.h>
#include <gtest/gtest.h>
#include <GeometricObjects/Cuboid.h>
#include <OutputWriter/XYZWriter.h>
#include <utils/ArrayUtils.h>
#include <random>
#include "SimulationLogic/LennardJonesSimulation.h"
#include <chrono>
#include <XML_Parser/BodyBuilder.h>
#include "XML_Parser/XMLParser.h"

/**
 * @brief Starts a LenardJonesSimulationTest and compares the result of two time steps with two files
 * containing the correct values
 */
TEST(SimulationTests, TestFullLennardJones) {
    XMLParser::parseXML("../src/Tests/TestInputFiles/LJTestInput.xml");
    XYZReader reader = XYZReader();
    LennardJonesSimulation lennardJonesSimulation = LennardJonesSimulation();
    ParticleContainer *particleContainer = new ParticleContainerDirectSum();
    Writer *w = new XYZWriter();
    std::vector<std::array<double, 3>> particles_1_Expected, particles_2_Expected, particles_1_test, particles_2_test;
    try {
        lennardJonesSimulation.simulate(*w, particleContainer);
        particles_1_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/Lennard_Test_0100.xyz");
        particles_2_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/Lennard_Test_0200.xyz");
        particles_1_test = reader.readOnlyPositions("Lennard_Test_0100.xyz");
        particles_2_test = reader.readOnlyPositions("Lennard_Test_0200.xyz");
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
void trivialLennardJonesCalculation(Particle &p1, Particle &p2, double epsilon, double rho) {
    double norm = ArrayUtils::L2Norm(p1.getX() - p2.getX());
    double term1 = -24.0*epsilon/pow(norm, 2);
    double term2 =  pow(rho/norm, 6);
    double term3 =  2 * pow(rho/norm, 12);
    auto diff =  term1 * (term2 - term3) * (p1.getX() - p2.getX());
    auto &f1 = p1.getFRef();
    auto &f2 = p2.getFRef();
    //faster than using ArrayUtils
    double temp;
    for (int j = 0; j < 3; ++j) {
        temp = diff[j];
        f1[j] += temp;
        f2[j] -= temp;
    }
}

/**
 * @brief Tests the current implementation Lennard Jones force calculation with the reference implementation
 */
TEST(SimulationTests, TestLennardJonesOptimization){
    int numberOfTries = 100000;

    double epsilon = 5;
    double rho = 1;
    BodyBuilder::rhoLookUpTable = {{rho}};
    BodyBuilder::epsilonLookUpTable = {{epsilon}};

    LJForceVisitor ljForceVisitor = LJForceVisitor(epsilon, rho);

    std::uniform_real_distribution<double> positionDistribution(0, 3);
    std::uniform_real_distribution<double> velocityDistribution(-10, 10);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());

    std::array<double, 3> randomPos1{};
    std::array<double, 3> randomPos2{};
    std::array<double, 3> randomVelocity1{};
    std::array<double, 3> randomVelocity2{};

    Particle p1{};
    Particle p2{};
    Particle p3{};
    Particle p4{};

    std::array<double, 3> result1{};
    std::array<double, 3> result2{};

    for (int i = 0; i < numberOfTries; ++i) {
        randomPos1 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};
        randomPos2 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};

        while (ArrayUtils::L2Norm(randomPos1-randomPos2) < 0.5){
            randomPos1 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};
            randomPos2 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};
        }

        randomVelocity1 = {velocityDistribution(re), velocityDistribution(re), velocityDistribution(re)};
        randomVelocity2 = {velocityDistribution(re), velocityDistribution(re), velocityDistribution(re)};

        p1 = Particle(randomPos1, randomVelocity1, 1, 0, 0);
        p2 = Particle(randomPos2, randomVelocity2, 1, 0, 0);

        p3 = p1;
        p4 = p2;

        ljForceVisitor.visitParticlePair(p1, p2);
        trivialLennardJonesCalculation(p3, p4, epsilon, rho);

        for (int j = 0; j < 3; ++j) {
            EXPECT_NEAR(p1.getF()[j], p3.getF()[j], 0.00001);
            EXPECT_NEAR(p2.getF()[j], p4.getF()[j], 0.00001);
        }
    }
}