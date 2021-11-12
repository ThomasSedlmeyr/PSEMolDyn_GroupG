//
// Created by thomas on 05.11.21.
//

#include "Body.h"

void Body::setInitialV(const std::array<double, 3> &initialV) {
    Body::initialV = initialV;
}

void Body::setPosition(const std::array<double, 3> &position) {
    Body::position = position;
}

std::array<double, 3> Body::parseLineWithThreeValues(const std::string &line) {
    //TODO diese Methode soll in der Lage sein eine string der drei werte enhält in einen Vector aus double Werten zu parsen
    return std::array<double, 3>();
}

void Body::parseInitialV(const std::string &line) {
    //TODO ich glaube hier werden die Werte kopiert eigntlich sollte eine Referenz übergabe ausreichen
    initialV = parseLineWithThreeValues(line);
}

void Body::parsePosition(const std::string &line) {
    position = parseLineWithThreeValues(line);
}


