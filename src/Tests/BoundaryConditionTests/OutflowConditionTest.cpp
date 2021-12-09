//
// Created by philip on 09.12.21.
//
#include <gtest/gtest.h>
#include <XML_Parser/XMLParser.h>
#include <BoundaryConditions/ReflectingCondition.h>
#include <SimulationLogic/LennardJonesSimulation.h>
#include <OutputWriter/VTKWriter.h>

/**
 * @brief Reads a cuboid from the input file that is already partly outside of the domain
 * and Test whether the particles outside of domain get deleted the first time the boundary conditions are applied
 */
TEST(BoundaryConditions, TestOutfowCondition){
    XMLParser::parseXML("../src/Tests/TestInputFiles/OutflowTestInput.xml");
    auto ljS = LennardJonesSimulation();
    std::array<int, 6> ones = {1,1,1,1,1,1};
    ParticleContainer *particleContainer = new ParticleContainerLinkedCells(10, 10, 10, 3, ones);
    Writer *writer = new VTKWriter();
    ljS.simulate(*writer, particleContainer);
    auto particles = particleContainer->getParticles();
    EXPECT_EQ(5*5*5-5*5-5*4-4*4, particles.size());
}