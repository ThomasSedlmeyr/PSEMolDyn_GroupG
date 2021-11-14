//
// Created by thomas on 05.11.21.
//

#include "Body.h"
#include <string>
#include <sstream>

void Body::setInitialV(const std::array<double, 3> &initialV) {
    Body::initialV = initialV;
}

void Body::setPosition(const std::array<double, 3> &position) {
    Body::position = position;
}

std::array<double, 3> Body::parseLineWithThreeValues(const std::string &line) {
    std::string stringValue;
    std::stringstream ss(line);
    std::array<double, 3> resultArray;

    int counter = 0;
    while(getline(ss, stringValue, ',')){
        resultArray[counter] += std::stod(stringValue);
        counter++;
    }
    return resultArray;
}

void Body::parseInitialV(const std::string &line) {
    //TODO ich glaube hier werden die Werte kopiert eigntlich sollte eine Referenz übergabe ausreichen
    initialV = parseLineWithThreeValues(line);
}

void Body::parsePosition(const std::string &line) {
    //TODO ich glaube hier werden die Werte kopiert eigntlich sollte eine Referenz übergabe ausreichen
    position = parseLineWithThreeValues(line);
}
int Body::getNumberParticles() const {
    return numberParticles;
}

const std::vector<Particle> &Body::getParticles() const {
    return particles;
}

Body::~Body() {

}

