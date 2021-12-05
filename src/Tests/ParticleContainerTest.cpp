//
// Created by philip on 01.12.21.
//
#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <random>
#include <chrono>
#include <SimulationLogic/ParticleContainerLinkedCells.h>
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
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(100, 100, 100, 3.0, {0, -10, 0});
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

}
