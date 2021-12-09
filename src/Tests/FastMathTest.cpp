#include <vector>
#include <gtest/gtest.h>
#include "utils/FastMath.h"
#include <random>
/**
 * @brief Test if the method checkIfSquareRootOfNumberIsBiggerThanCertainValue works properly.
 * For testing this we create several random cutOffs and test the function on random distances.
 */
TEST(GeneralTests, TestcheckIfSquareRootOfNumberIsBiggerThanCertainValue) {
    std::random_device rd; //get a random number from the pc
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<double> cutOffRange(2, 4); //define the range

    for(int i = 0; i < 10; i++) {
        double cutOffRadius = cutOffRange(gen);
        std::uniform_real_distribution<double> distanceRange(0, sqrt(3)*cutOffRadius); //define the range
        for (int n = 0; n < 50; ++n) {
            double randomNumber = distanceRange(gen);
            bool correctResult = sqrt(randomNumber) > cutOffRadius;
            EXPECT_EQ(correctResult, checkIfSquareRootOfNumberIsBiggerThanCertainValue(randomNumber, cutOffRadius));
        }
    }
}