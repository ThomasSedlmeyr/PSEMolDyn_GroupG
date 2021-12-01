#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <InputReader/ArgumentContainer.h>
#include <random>
#include <chrono>
#include <SimulationLogic/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"

/**
 * @brief Tests if ArgumentContainer parses file correctly
 */
TEST(Tests, readParamsTest) {
    ArgumentContainer container;
    bool ret = container.readParamsAndValues("../src/Tests/TestInputFiles/ParamsLJtest.txt");
    EXPECT_EQ(ret, true);
    EXPECT_DOUBLE_EQ(container.getValueToParam("epsilon"), 5.0);
    EXPECT_DOUBLE_EQ(container.getValueToParam("mass"), 1.0);
    EXPECT_DOUBLE_EQ(container.getValueToParam("rho"), 1.0);
    EXPECT_DOUBLE_EQ(container.getValueToParam("h"), 1.125);
}
