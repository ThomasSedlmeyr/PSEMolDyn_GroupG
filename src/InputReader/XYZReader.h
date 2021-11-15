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
    bool readFile(const std::string& fileName);

    const std::vector<std::tuple<std::string, std::array<double, 3>>> &getMolecules() const;

private:
    std::vector<std::tuple<std::string,std::array<double, 3>>> molecules;
};


#endif //PSEMOLDYN_GROUPG_XYZREADER_H
