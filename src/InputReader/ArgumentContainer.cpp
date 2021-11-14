//
// Created by thomas on 12.11.21.
//

#include "ArgumentContainer.h"
#include <string>
#include <fstream>

bool ArgumentContainer::checkIfParamsMatchParamsAndValues(std::vector<std::string> params) {
    //TODO Methode schreiben, die checkt ob alle params in der paramsAndValues enthalten sind
    return false;
}

void ArgumentContainer::readParamsAndValues(const std::string &filename) {
    //if the fileName is empty this means for this simulation type there does not exist anyParams
    if(filename.empty()){
        paramsAndValues = {};
        return;
    }
    //TODO Methode schreiben, die paramsAndValues aus einer Datei einlesen kann. Beispieldatei ParamsLenardJonesSimulation.txt
    std::ifstream file(filename);
    std::string x;
    double y;
    while (file >> x >> y) {
        // clang says to use emplace instead of push
        paramsAndValues.emplace_back(x, y);
    }
}

double ArgumentContainer::getValueToParam(const std::string &param) {
    //TODO Methode schreiben, die den zugehörigen param den richtigen float Wert zurückgibt
    auto temp = paramsAndValues;
    double erg = 0;
    for (int i = 0; i < paramsAndValues.size(); ++i) {
        if (param == std::get<0>(temp.back())){
            erg = std::get<1>(temp.back());
            break;
        }
        temp.pop_back();
    }
    return erg;
}
