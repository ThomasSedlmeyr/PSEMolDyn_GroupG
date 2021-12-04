#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <chrono>
#include <SimulationLogic/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "outputWriter/XYZWriter.h"

TEST(Tests, CheckIfSpecificCellsHaveRightSizes) {
    double domainSizeX = 20;
    double domainSizeY = 30;
    double domainSizeZ = 40;
    std::array<int, 6> ones = {1, 1, 1, 1, 1, 1};
    ParticleContainerLinkedCells particleContainer(domainSizeX, domainSizeY, domainSizeZ, 3, {0, 0, 0});
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
    EXPECT_EQ(domainSizeX * domainSizeY, boundaryConditions[0]->getSpecificHaloCells().size());
}