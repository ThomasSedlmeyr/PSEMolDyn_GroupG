//
// Created by philip on 01.12.21.
//

#include <vector>
#include <tuple>
#include <InputReader/XYZReader.h>
#include <gtest/gtest.h>
#include <SimulationLogic/GravitationSimulation.h>
#include <OutputWriter/XYZWriter.h>
#include "XML_Parser/XMLParser.h"

/**
 * @brief Starts a GravitationSimulation and compares the result of two time steps with two files
 * containing the correct values
 */
TEST(SimulationTests, TestFullGravitation) {
    XMLParser::parseXML("../src/Tests/TestInputFiles/GravTestInput.xml");
    XYZReader reader = XYZReader();
    GravitationSimulation gravitationSimulation = GravitationSimulation();
    Writer *w = new XYZWriter();
    std::vector<std::array<double, 3>> particles_1_Expected, particles_2_Expected, particles_1_test, particles_2_test;
    try {
        ParticleContainer *particleContainer = new ParticleContainerDirectSum();
        gravitationSimulation.simulate(*w, particleContainer);
        particles_1_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/Grav_Test_0500.xyz");
        particles_2_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/Grav_Test_1000.xyz");
        particles_1_test = reader.readOnlyPositions("Grav_Test_0500.xyz");
        particles_2_test = reader.readOnlyPositions("Grav_Test_1000.xyz");
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
