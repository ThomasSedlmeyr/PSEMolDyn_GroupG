#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <GeometricObjects/Cuboid.h>
#include <chrono>
#include <ParticleContainers/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "OutputWriter/XYZWriter.h"

TEST(Tests, CheckIfSpecificCellsHaveRightSizes) {
    double cutOff = 3.0;
    double domainSizeX = 20;
    double domainSizeY = 30;
    double domainSizeZ = 40;
    int numberCellsX = ((int) domainSizeX / cutOff) + 2;
    int numberCellsY = ((int) domainSizeY / cutOff) + 2;
    int numberCellsZ = ((int) domainSizeZ / cutOff) + 2;

    std::array<int, 6> ones = {1, 1, 1, 1, 1, 1};
    ParticleContainerLinkedCells particleContainer(domainSizeX, domainSizeY, domainSizeZ, cutOff, ones);
    auto boundaryConditionContainer = std::make_unique<BoundaryConditionContainer>(ones,
                                                                                   ParticleContainerLinkedCells::boundaryCells,
                                                                                   ParticleContainerLinkedCells::haloCells,
                                                                                   ParticleContainerLinkedCells::numberCellsX,
                                                                                   ParticleContainerLinkedCells::numberCellsY,
                                                                                   ParticleContainerLinkedCells::numberCellsZ,
                                                                                   std::array<double, 3>{domainSizeX,
                                                                                                         domainSizeY,
                                                                                                         domainSizeZ});

    std::array<BoundaryCondition *, 6> boundaryConditions = boundaryConditionContainer->getBoundaryConditions();

    //Test front
    EXPECT_EQ(numberCellsX * numberCellsY, boundaryConditions[0]->getSpecificHaloCells().size());
    EXPECT_EQ((numberCellsX - 2) * (numberCellsY - 2), boundaryConditions[0]->getSpecificBoundaryCells().size());
    //Test back
    EXPECT_EQ(numberCellsX * numberCellsY, boundaryConditions[2]->getSpecificHaloCells().size());
    EXPECT_EQ((numberCellsX - 2) * (numberCellsY - 2), boundaryConditions[2]->getSpecificBoundaryCells().size());

    //Test right side
    EXPECT_EQ(numberCellsZ * numberCellsY, boundaryConditions[1]->getSpecificHaloCells().size());
    EXPECT_EQ((numberCellsZ - 2) * (numberCellsY - 2), boundaryConditions[1]->getSpecificBoundaryCells().size());
    //Test left side
    EXPECT_EQ(numberCellsZ * numberCellsY, boundaryConditions[3]->getSpecificHaloCells().size());
    EXPECT_EQ((numberCellsZ - 2) * (numberCellsY - 2), boundaryConditions[3]->getSpecificBoundaryCells().size());

    //Test top side
    EXPECT_EQ(numberCellsZ * numberCellsX, boundaryConditions[4]->getSpecificHaloCells().size());
    EXPECT_EQ((numberCellsZ - 2) * (numberCellsX - 2), boundaryConditions[4]->getSpecificBoundaryCells().size());
    //Test bottom side
    EXPECT_EQ(numberCellsZ * numberCellsX, boundaryConditions[5]->getSpecificHaloCells().size());
    EXPECT_EQ((numberCellsZ - 2) * (numberCellsX - 2), boundaryConditions[5]->getSpecificBoundaryCells().size());
}