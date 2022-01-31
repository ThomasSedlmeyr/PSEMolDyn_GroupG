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
    subdomainContainer.generateSubdomainsWithNumberOfThreads(28);

    //We first check if get the correct number of Subdomains
    EXPECT_EQ(28, subdomainContainer.getSubdomains().size());
}

/**
 * @brief Test if the split in equal parts works as expected
 */
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

/**
 * @brief Tests if we get the correct number of Subdomains
 */
TEST(ParallelAlgorithmsTests, TestForCorrectNumberOfSubdomains) {
    std::array<int, 6> ones = {1,1,1,1,1,1};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(60, 60, 60, 3.6, ones);

    SubdomainContainer subdomainContainer{};
    std::array<int, 9> numberOfThreads = {2,4,8,14,16,28,56,64,256};

    for (int i = 0; i < numberOfThreads.size(); ++i) {
        subdomainContainer.generateSubdomainsWithNumberOfThreads(numberOfThreads[i]);
        EXPECT_EQ(numberOfThreads[i], subdomainContainer.getSubdomains().size());
    }
}

/**
 * @brief Tests if the SubdomainCells were set correct to synchronized
 */
TEST(ParallelAlgorithmsTests, TestForCorrectSynchronizationOfSubdomains) {
    std::array<int, 6> ones = {1, 1, 1, 1, 1, 1};
    ParticleContainerLinkedCells particleContainerLinkedCells = ParticleContainerLinkedCells(35, 35, 35, 3.6, ones);

    SubdomainContainer subdomainContainer{};
    subdomainContainer.generateSubdomainsWithNumberOfThreads(8);
    std::vector<Subdomain *> subdomains = subdomainContainer.getSubdomains();

    std::vector<SubdomainCell> subdomainCells = std::vector<SubdomainCell>();
    for(auto& subdomain : subdomains){
        auto cells = subdomain->getCells();
        for(auto& subdomainCell : *cells){
            subdomainCells.push_back(subdomainCell);
        }
    }

    std::array<std::array<int, 3>, 7> cellsWhichHaveToBeSynchronized = {{{2,0,0},{3,0,0},{5,0,0},{6,0,5},{5,0,11},{0,0,5},{10,0,5}}};
    for(auto subdomainCell : subdomainCells){
        for(auto& position : cellsWhichHaveToBeSynchronized){
            auto cell = subdomainCell.getPointerToCell();
            auto cellPosition = cell->getRelativePositionInDomain();
            if(position[0] == cellPosition[0] && position[1] == cellPosition[1] && position[2] == cellPosition[2]){
                EXPECT_EQ(true, subdomainCell.getIsSynchronized());
            }
        }
    }
}