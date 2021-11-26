//
// Created by thomas on 24.11.21.
//

#include "Cell.h"

double Cell::sizeX = -1;
double Cell::sizeY = -1;
double Cell::sizeZ = -1;

void Cell::calculateDimensions(double cutOffRadius) {

}

Cell::Cell(const std::vector<Particle> &particles, const std::array<double, 3> &position, int cellType) :
        particles(particles), position(position), cellType(cellType) {}

Cell::Cell(const std::array<double, 3> &position, int cellType) :
        position(position), cellType(cellType) {}

Cell::Cell() {

}
