//
// Created by thomas on 24.11.21.
//

#include "Cell.h"

#include <utility>

double Cell::sizeX = -1;
double Cell::sizeY = -1;
double Cell::sizeZ = -1;

void Cell::calculateDimensions(double cutOffRadius) {

}

Cell::Cell(std::vector<Particle> particles, const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType) :
        particles(std::move(particles)), position(position), relativePositionInDomain(relativePositionInDomain), cellType(cellType) {}

Cell::Cell(const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType) :
        position(position), relativePositionInDomain(relativePositionInDomain), cellType(cellType) {}

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

const std::array<int, 3> &Cell::getRelativePositionInDomain() const {
    return relativePositionInDomain;
}

Cell::Cell(std::vector<Particle> particles, const std::array<double, 3> &position, int cellType):
    particles(std::move(particles)), position(position),  cellType(cellType) {}


Cell::Cell(const std::array<double, 3> &position, int cellType) :
    position(position), cellType(cellType) {}

void Cell::setRelativePositionInDomain(const std::array<int, 3> &relativePositionInDomain) {
    Cell::relativePositionInDomain = relativePositionInDomain;
}

