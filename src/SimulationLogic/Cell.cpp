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

int Cell::getCellType() const {
    return cellType;
}

const std::array<double, 3> &Cell::getPosition() const {
    return position;
}

const int Cell::getInnerCellValue() {
    return INNER_CELL;
}

const int Cell::getBoundaryCellValue() {
    return BOUNDARY_CELL;
}

const int Cell::getHaloCellValue() {
    return HALO_CELL;
}

std::vector<Particle> &Cell::getParticles() {
    return particles;
}

std::vector<Cell *> &Cell::getNeighbourCells() {
    return neighbourCells;
}

void Cell::addCellToNeighbours(Cell *pCell) {
    neighbourCells.push_back(pCell);
}

bool Cell::operator==(Cell &other) {
    return position == other.getPosition();
}
