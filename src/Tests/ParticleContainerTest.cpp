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
    particleContainer.createCells();

    for (int i = 0; i < particleContainer.getHaloCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getHaloCells()[i]->getCellType(),Cell::getHaloCellValue());
    }
    for (int i = 0; i < particleContainer.getBoundaryCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getBoundaryCells()[i]->getCellType(),Cell::getBoundaryCellValue());
    }
    for (int i = 0; i < particleContainer.getInnerCells().size(); ++i) {
        EXPECT_EQ(particleContainer.getInnerCells()[i]->getCellType(),Cell::getInnerCellValue());
    }
}

TEST(ParticleContainerTests, addParticleToContainerTest){
    std::uniform_real_distribution<double> positionDistribution(0, 100);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    ParticleContainerLinkedCells particleContainer = ParticleContainerLinkedCells(100, 100, 100, 3.0);
    std::array<double, 3> randomPos1{};
    Particle p{};
    for (int i = 0; i < 100000; ++i) {
        randomPos1 = {positionDistribution(re), positionDistribution(re), positionDistribution(re)};
        p.setX(randomPos1);
        particleContainer.addParticleToContainer(p);
        Cell cellContainingParticle = particleContainer.getCells()[particleContainer.getCellIndexForParticle(p)];
        for (int j = 0; j < 3; ++j) {
            if (cellContainingParticle.getPosition()[j] > randomPos1[j] || cellContainingParticle.getPosition()[j]+Cell::sizeX < randomPos1[j]){
                FAIL();
            }
        }
    }
}

/**
 * @brief tests if for different ParticleContainers the simulation result after one
 * time steps is the same
 */
TEST(ParticleContainerTests, compareContainers) {

}
