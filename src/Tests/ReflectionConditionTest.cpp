#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <random>
#include <chrono>
#include <SimulationLogic/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"

/**
 * @brief Test if the method checkIfSquareRootOfNumberIsBiggerThanCertainValue works properly.
 * For testing this we create several random cutOffs and test the function on random distances.
 */
TEST(Tests, checkIfSquareRootOfNumberIsBiggerThanCertainValueTest) {
    auto ljS = LennardJonesSimulation();
    ParticleContainerLinkedCells particleContainer(70, 40, 6, 3, {0, 0, 0});
}