//
// Created by thomas on 12.11.21.
//

#ifndef PSEMOLDYN_GROUPG_ARGUMENTCONTAINER_H
#define PSEMOLDYN_GROUPG_ARGUMENTCONTAINER_H

#include <vector>
#include <string>
#include <tuple>
class ArgumentContainer {

private:
    std::vector<std::tuple<std::string, double>> paramsAndValues;

public:
    bool checkIfParamsMatchParamsAndValues(std::vector<std::string> params);
    void readParamsAndValues(const std::string& filename);
    double getValueToParam(const std::string& param);


};


#endif //PSEMOLDYN_GROUPG_ARGUMENTCONTAINER_H
