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

TEST(ParallelAlgorithmsTests, TestSplitInNearlyEqualParts) {
    SubdomainContainer subdomainContainer{};
    std::array<int, 31> testValues = {};
    for (int i = 7; i < testValues.size()+7; i++){
        testValues[i-7] = i;
    }

    std::array<int, 3> testNumberPartsValues = {2,4,7};
    for (auto& testValue : testValues) {
        for(auto& testNumberPartValue : testNumberPartsValues){
            std::vector<int> nearlyEqualParts = std::vector<int>(testNumberPartValue);
            subdomainContainer.splitInNearlyEqualParts(testValue, testNumberPartValue, nearlyEqualParts);
            int sum = 0;
            int lowerValue = testValue / testNumberPartValue;
            int upperValue = lowerValue + 1;

            for(auto& nearlyEqualPart : nearlyEqualParts){
                sum += nearlyEqualPart;
                if(nearlyEqualPart != lowerValue && nearlyEqualPart != upperValue){
                    std::cout << "value should be either: " << lowerValue << " or: " << upperValue << " but was: " << nearlyEqualPart << std::endl;
                    FAIL();
                }
            }
            EXPECT_EQ(sum, testValue);
        }
    }
}

TEST(ParallelAlgorithmsTests, TestForCorrectNumberOfComputationTasks) {
    std::array<int, 6> ones = {1,1,1,1,1,1};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(60, 60, 60, 3.6, ones);

    SubdomainContainer subdomainContainer{};
    std::array<int, 6> numberOfThreads = {2,4,8,14,16,28};

    for (int i = 0; i < numberOfThreads.size(); ++i) {
        subdomainContainer.generateSubdomainsWithNumberOfThreads2(numberOfThreads[i]);
        EXPECT_EQ(numberOfThreads[i], subdomainContainer.getSubdomains().size());
    }

}