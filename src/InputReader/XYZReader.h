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
    std::vector<std::tuple<std::string, std::array<double, 3>>>  readParticles(const std::string& fileName);
    std::vector<std::array<double, 3>>  readOnlyPositions(const std::string& fileName);
};


#endif //PSEMOLDYN_GROUPG_XYZREADER_H
