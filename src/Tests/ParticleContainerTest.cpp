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

TEST(ParticleContainerTests, checkLinkedCellStucture){
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(100, 100, 6, 3.0);
    particleContainer.cellsToXYZ();
}

TEST(ParticleContainerTests, checkHaloBoundaryAndInnerCells){
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(10, 10, 10, 3.0);

    for (std::size_t i = 0; i < ParticleContainerLinkedCells::getHaloCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getHaloCells()[i]->getCellType(),Cell::getHaloCellValue());
    }
    for (std::size_t i = 0; i < ParticleContainerLinkedCells::getBoundaryCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getBoundaryCells()[i]->getCellType(),Cell::getBoundaryCellValue());
    }
    for (std::size_t i = 0; i < ParticleContainerLinkedCells::getInnerCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getInnerCells()[i]->getCellType(),Cell::getInnerCellValue());
    }
}

TEST(ParticleContainerTests, addParticleToContainerTest){
    std::uniform_real_distribution<double> positionDistribution(0, 80);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(100, 100, 100, 3.0);
    std::array<double, 3> randomPos1{};
    Particle p{};
    for (int i = 0; i < 1000; ++i) {
        randomPos1 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};
        p.setX(randomPos1);
        particleContainer.addParticleToContainer(p);
        Cell cellContainingParticle = particleContainer.getCells()[ParticleContainerLinkedCells::getCellIndexForParticle(p)];
        EXPECT_TRUE(cellContainingParticle.particleLiesInCell(p));
    }
}

/**
 * @brief test if we get the same results for the ParticleContainerLinkedCells and for ParticleContainerDirectSum.
 */
TEST(ParticleContainerTests, compareContainers) {
    std::array<int, 6> ones = {1,1,1,1,1,1};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(100, 100, 100, 3.0, ones);
    ParticleContainerDirectSum particleContainerDirectSum = ParticleContainerDirectSum();
    //ParticleContainerDirectSum particleContainerLinkedCells = ParticleContainerDirectSum();
    Writer* writer1 = new VTKWriter();
    Writer* writer2 = new VTKWriter();
    LennardJonesSimulation s1 = LennardJonesSimulation();
    LennardJonesSimulation s2 = LennardJonesSimulation();
    s1.simulate(0.002, 0.1, *writer1, 1, "../src/Tests/TestInputFiles/ParamsLJtest.txt",
                 "../src/Tests/TestInputFiles/TwoCuboidsLJ_Test.txt", "DirectSumTest", &particleContainerDirectSum);

    s2.simulate(0.002, 0.1, *writer2, 1, "../src/Tests/TestInputFiles/ParamsLJtest.txt",
                "../src/Tests/TestInputFiles/TwoCuboidsLJ_Test.txt", "LinkedCellsTest", &particleContainerLinkedCells);
    auto particles1 = particleContainerDirectSum.getParticles();
    auto particles2 = particleContainerLinkedCells.getParticles();

    for (int i = 0; i < particles2.size(); ++i) {
        std::cout << "particle: " << i << std::endl;
        for (int j = 0; j < 2; ++j) {
            EXPECT_NEAR(particles1[i].getX()[j], particles2[i].getX()[j], 0.001);
        }
    }
}