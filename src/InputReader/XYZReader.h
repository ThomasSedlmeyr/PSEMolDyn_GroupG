//
// Created by thomas on 12.11.21.
//

#ifndef PSEMOLDYN_GROUPG_XYZREADER_H
#define PSEMOLDYN_GROUPG_XYZREADER_H
#include <tuple>
#include <string>
#include <vector>

class XYZReader {
public:
    /**
     * @brief
     * @param fileName the name of the xyz-file which should be read
     * @return a vector containing tuples which contain the name of the particle and the position
     */
    std::vector<std::tuple<std::string, std::array<double, 3>>>  readParticles(const std::string& fileName);

    /**
     * @brief
     * @param fileName the name of the xyz-file which should be read
     * @return a vector containing an array which contains the position of every particle
     */
    std::vector<std::array<double, 3>>  readOnlyPositions(const std::string& fileName);
};


#endif //PSEMOLDYN_GROUPG_XYZREADER_H
