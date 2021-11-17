//
// Created by thomas on 07.11.21.
//

#include "Tests.h"
#include <vector>
#include <string>
#include <tuple>
#include <InputReader/XYZReader.h>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <InputReader/ArgumentContainer.h>
#include <SimulationLogic/GravitationSimulation.h>
#include <outputWriter/XYZWriter.h>

TEST(Tests, GravitationSimulationTest) {
    XYZReader reader = XYZReader();
    GravitationSimulation gravitationSimulation = GravitationSimulation();
    Writer *w = new XYZWriter();
    std::vector<std::array<double, 3>> particles_1_Expected, particles_2_Expected, particles_1_test, particles_2_test;
    try {
        gravitationSimulation.simulate(10, 0.01, *w, 500, "", "../src/Tests/TestInputFiles/eingabe-sonne.txt", "Grav_Test");
        particles_1_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/MD_vtk_0500.xyz");
        particles_2_Expected = reader.readOnlyPositions("../src/Tests/ReferenceTestFiles/MD_vtk_1000.xyz");
        particles_1_test= reader.readOnlyPositions("Grav_Test_0500.xyz");
        particles_2_test = reader.readOnlyPositions("Grav_Test_1000.xyz");
    }catch(const std::exception& e){
        FAIL();
    }
    for (int i = 0; i < particles_2_Expected.size(); ++i) {
        EXPECT_NEAR(particles_1_Expected[i][0], particles_1_test[i][0], 0.0000001);
        EXPECT_NEAR(particles_1_Expected[i][1], particles_1_test[i][1], 0.0000001);
        EXPECT_NEAR(particles_1_Expected[i][2], particles_1_test[i][2], 0.0000001);
        EXPECT_NEAR(particles_2_Expected[i][0], particles_2_test[i][0], 0.0000001);
        EXPECT_NEAR(particles_2_Expected[i][1], particles_2_test[i][1], 0.0000001);
        EXPECT_NEAR(particles_2_Expected[i][2], particles_2_test[i][2], 0.0000001);
    }
}

TEST(Tests, CuboidTest){
    Cuboid cuboid = Cuboid(0, 1, 1);
    std::array<double, 3> structure = {40, 16, 8};
    cuboid.setStructure(structure);
    cuboid.generateParticles(0);
    EXPECT_EQ(cuboid.getParticles().size(), structure[0]*structure[1]*structure[2]);
}

TEST(Tests, readParamsTest) {
    ArgumentContainer container;
    bool ret = container.readParamsAndValues("../src/Tests/TestInputFiles/ParamsLennardJonesSimulation.txt");
    EXPECT_EQ(ret, true);
    EXPECT_DOUBLE_EQ(container.getValueToParam("epsilon"), 5.0);
    EXPECT_DOUBLE_EQ(container.getValueToParam("mass"), 1.0);
    EXPECT_DOUBLE_EQ(container.getValueToParam("rho"), 1.0);
    EXPECT_DOUBLE_EQ(container.getValueToParam("h"), 1.125);
}