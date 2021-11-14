//
// Created by thomas on 12.11.21.
//

#include "ArgumentContainer.h"
#include <string>
#include <fstream>

bool ArgumentContainer::checkIfParamsMatchParamsAndValues(std::vector<std::string> params) {
    bool isCorrect = false;
    for(auto param : params){
        isCorrect = false;
        for(auto paramAndValue : paramsAndValues){
            if(std::get<0>(paramAndValue).compare(param) == 0){
                isCorrect = true;
                break;
            }
        }
        if(!isCorrect){
            return false;
        }
    }
    return true;
}

bool ArgumentContainer::readParamsAndValues(const std::string &filename) {
    //if the fileName is empty this means for this simulation type there does not exist anyParams
    if(filename.empty()){
        paramsAndValues = {};
        return true;
    }
    std::ifstream file(filename);
    std::string x;
    double y;
    while (file >> x >> y) {
        paramsAndValues.emplace_back(x, y);
    }
    //TODO hier sollte eine Fehlerbehandlung erfolgen
    return true;
}

double ArgumentContainer::getValueToParam(const std::string &param) {
    auto temp = paramsAndValues;
    double erg = 0;
    for (long unsigned int i = 0; i < paramsAndValues.size(); ++i) {
        if (param.compare(std::get<0>(temp.back())) == 0){
            erg = std::get<1>(temp.back());
            break;
        }
        temp.pop_back();
    }
    return erg;
}
