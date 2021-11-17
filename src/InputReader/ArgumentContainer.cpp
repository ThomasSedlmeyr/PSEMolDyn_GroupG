//
// Created by thomas on 12.11.21.
//

#include "ArgumentContainer.h"
#include <string>
#include <fstream>
#include <iostream>

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
    try {
        std::ifstream file(filename);
        std::string x;
        double y;
        while (file >> x >> y) {
            paramsAndValues.emplace_back(x, y);
        }
    } catch (std::bad_exception) {
        // error handling, filename faulty
        printErrorMessage();
        // terminate program as further run not possible
        exit(EXIT_FAILURE);
    }
    return true;
}

void ArgumentContainer::printErrorMessage(){
    std::cout << "File for reading parameters is faulty!" << std::endl;
    std::cout << "Please try again with correctly formatted file with the required parameters." << std::endl;
    std::cout << "For help consult the readMe." << std::endl;
}

double ArgumentContainer::getValueToParam(const std::string &param) {
    for (long unsigned int i = 0; i < paramsAndValues.size(); ++i) {
        std::tuple<std::string, double> &paramAndValue = paramsAndValues[i];
        if (param.compare(std::get<0>(paramAndValue)) == 0){
            return std::get<1>(paramAndValue);
        }
    }
    //TODO was machen wir, wenn hier ein Fehler auftritt?
    printErrorMessage();
    // soll hier terminiert werden?
    exit(EXIT_FAILURE);
}
