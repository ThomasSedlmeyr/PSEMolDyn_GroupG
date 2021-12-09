//
// Created by philip on 01.12.21.
//
#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <GeometricObjects/Cuboid.h>
#include <random>
#include <chrono>
#include <ParticleContainers/ParticleContainerLinkedCells.h>
#include <ParticleContainers/ParticleContainerDirectSum.h>
#include <SimulationLogic/LennardJonesSimulation.h>
#include <OutputWriter/VTKWriter.h>
#include "SimulationLogic/Cell.h"
#include "XML_Parser/XMLParser.h"


/**
 * @brief this test can be used to create a visualization of the LinkedCellStructure
 */
TEST(ParticleContainerTests, VisualizeLinkedCellStructure) {
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(100, 100, 6, 3.0);
    particleContainer.cellsToVTK();
}

/**
 * @brief This test checks for every pointer in the halo-, boundary and innerCell, that all these particles have the correct type
 */
TEST(ParticleContainerTests, TestHaloBoundaryAndInnerCells) {
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(10, 10, 10, 3.0);

    for (std::size_t i = 0; i < ParticleContainerLinkedCells::getHaloCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getHaloCells()[i]->getCellType(), Cell::getHaloCellType());
    }
    for (std::size_t i = 0; i < ParticleContainerLinkedCells::getBoundaryCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getBoundaryCells()[i]->getCellType(), Cell::getBoundaryCellType());
    }
    for (std::size_t i = 0; i < ParticleContainerLinkedCells::getInnerCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getInnerCells()[i]->getCellType(), Cell::getInnerCellType());
    }
}

/**
 * @brief This Test inserts random particles into the boundary and checks if the particle was insert at
 * the correct position
 */
TEST(ParticleContainerTests, TestAddParticleToContainer){
    std::uniform_real_distribution<double> positionDistribution(0, 80);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(100, 100, 100, 3.0);
    std::array<double, 3> randomPos1{};
    Particle p{};
    for (int i = 0; i < 1000; ++i) {
        randomPos1 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};
        p.setX(randomPos1);
        particleContainer.addParticleToContainer(p);
        Cell cellContainingParticle = ParticleContainerLinkedCells::getCells()[ParticleContainerLinkedCells::getCellIndexForParticle(p)];
        EXPECT_TRUE(cellContainingParticle.particleLiesInCell(p));
    }
}

/**
 * @brief Helper function to sort particle vector
 * @param p1
 * @param p2
 * @return
 */
bool sortParticlesById(Particle &p1, Particle &p2){
    return p1.getId() < p2.getId();
}

/**
 * @brief Tests if we get the same results for the ParticleContainerLinkedCells and for ParticleContainerDirectSum.
 */
TEST(ParticleContainerTests, TestDifferentContainers) {
    std::array<int, 6> ones = {1,1,1,1,1,1};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(100, 100, 100, 3.0, ones);
    ParticleContainerDirectSum particleContainerDirectSum = ParticleContainerDirectSum();
    Writer* writer1 = new VTKWriter();
    Writer* writer2 = new VTKWriter();
    LennardJonesSimulation s1 = LennardJonesSimulation();
    LennardJonesSimulation s2 = LennardJonesSimulation();

    XMLParser::parseXML("../src/Tests/TestInputFiles/DirectSumInput.xml");
    s1.simulate(*writer1, &particleContainerDirectSum);
    XMLParser::resetInternalData();
    XMLParser::parseXML("../src/Tests/TestInputFiles/LinkedCellsInput.xml");
    s2.simulate(*writer2, &particleContainerLinkedCells);

    auto particles1 = particleContainerDirectSum.getParticles();
    auto particles2 = particleContainerLinkedCells.getParticles();
    std::sort(particles2.begin(), particles2.end(), sortParticlesById);
    for (int i = 0; i < particles2.size(); ++i) {
        std::cout << "particle: " << i << std::endl;
        EXPECT_EQ(particles1[i].getId(), particles2[i].getId());
        for (int j = 0; j < 2; ++j) {
            EXPECT_NEAR(particles1[i].getX()[j], particles2[i].getX()[j], 0.05);
        }
    }
}