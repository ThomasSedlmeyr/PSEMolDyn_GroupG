//
// Created by thomas on 12.11.21.
//

#include "ArgumentContainer.h"
#include <string>

bool ArgumentContainer::checkIfParamsMatchParamsAndValues(std::vector<std::string> params) {
    //TODO Methode schreiben, die checkt ob alle params in der paramsAndValues enthalten sind
    return false;
}

void ArgumentContainer::readParamsAndValues(const std::string &filename) {
    //if the fileName is empty this means for this simulation type there does not exist anyParams
    if(filename.compare("") == 0){
        paramsAndValues = {};
        return;
    }
    //TODO Methode schreiben, die paramsAndValues aus einer Datei einlesen kann. Beispieldatei ParamsLenardJonesSimulation.txt

}

double ArgumentContainer::getValueToParam(const std::string &param) {
    //TODO Methode schreiben, die den zugehörigen param den richtigen float Wert zurückgibt
    return 0;
}
