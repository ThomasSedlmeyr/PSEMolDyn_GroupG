//
// Created by philip on 31.01.22.
//
#include <gtest/gtest.h>
#include "utils/SmoothedLJForceCalculation.h"

TEST(SimulationTests, TestSmoothedLJ) {
    BodyBuilder::epsilonLookUpTable = {{1}};
    BodyBuilder::rhoLookUpTable = {{1}};
    XMLParser::crystallization_r_l_p = 1.9;
    XMLParser::crystallization_r_c_p = 2.3;
    std::array<double, 3> pos1 = {1.0,1,1};
    std::array<double, 3> pos2 = {3.0,1,1};
    Particle p1 = Particle(pos1, {0,0,0}, 1);
    Particle p2 = Particle(pos2, {0,0,0}, 1);
    calculateSmoothedLJForce(p1, p2, pos1, pos2, true);
    auto f1 = p1.getF();
    auto f2 = p2.getF();
    EXPECT_GT(f1[0], 0);
    EXPECT_LT(f2[0], 0);
}