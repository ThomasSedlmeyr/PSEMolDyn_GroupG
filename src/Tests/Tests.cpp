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


bool Tests::testForce() {
    XYZReader reader = XYZReader();
    if(!reader.readFile("../Tests/ReferenceTestFiles/MD_vtk_0500.xyz")) return false;
    std::vector<std::tuple<std::string,std::array<double, 3>>> molecules = reader.getMolecules();
}

TEST(Tests, CuboidTest){
    Cuboid cuboid = Cuboid(0, 1, 1);
    std::array<double, 3> structure = {40, 16, 8};
    cuboid.setStructure(structure);
    cuboid.generateParticles(0);
    EXPECT_EQ(cuboid.getParticles().size(), structure[0]*structure[1]*structure[2]);
}
