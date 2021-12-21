#include "Body.h"
#include <sstream>

Body::Body(int ID, double meshWidth, double massPerParticle) {
    this->ID = ID;
    this->meshWidth = meshWidth;
    this->massPerParticle = massPerParticle;
}

std::array<double, 3> Body::parseLineWithThreeValues(const std::string &line) {
    std::string stringValue;
    std::stringstream ss(line);
    std::array<double, 3> resultArray{};

    int counter = 0;
    while(getline(ss, stringValue, ',')){
        resultArray[counter] += std::stod(stringValue);
        counter++;
    }
    return resultArray;
}

void Body::parseInitialV(const std::string &line) {
    initialV = parseLineWithThreeValues(line);
}

void Body::parsePosition(const std::string &line) {
    position = parseLineWithThreeValues(line);
}

std::vector<Particle> & Body::getParticles() {
    return particles;
}

const std::array<double, 3> &Body::getInitialV() const {
    return initialV;
}

double Body::getMeshWidth() const {
    return meshWidth;
}

Body::~Body() = default;
