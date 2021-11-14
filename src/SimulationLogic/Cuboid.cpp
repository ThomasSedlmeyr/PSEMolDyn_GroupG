//
// Created by thomas on 05.11.21.
//

#include "Cuboid.h"
Cuboid :: Cuboid(){}





void Cuboid::parseStructure(const std::string &line) {

}

std::vector<Particle> Cuboid::generateParticles() {
    //TODO Hier sollen mit Hilfe der Dimensionen und der anderen Eigeschaftena alle Partikel des Quaders erstellt werden
    return std::vector<Particle>();
}

void Cuboid::setStructure(const std::array<double, 3> &dim){
    Cuboid::dimensions = dim;
}