#include <vector>
#include <gtest/gtest.h>
#include "utils/FastMath.h"
#include "SimulationLogic/SubdomainContainer.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

/**
 * @brief Tests if we get the correct Subdomain-Structure
 */
TEST(ParallelAlgorithmsTests, TestForCorrectPartition) {
    std::array<int, 6> ones = {1,1,1,1,1,1};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(21, 12, 110, 1.0, ones);

    SubdomainContainer subdomainContainer{};
    subdomainContainer.generateSubdomains(5, 4, 17);

    //We first check if get the correct number of Subdomains
    EXPECT_EQ(4*3*6, subdomainContainer.getSubdomains().size());
}