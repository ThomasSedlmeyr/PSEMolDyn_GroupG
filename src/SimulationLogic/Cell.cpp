//
// Created by thomas on 24.11.21.
//

#include "Cell.h"

#include <utility>

double Cell::sizeX = -1;
double Cell::sizeY = -1;
double Cell::sizeZ = -1;

Cell::Cell(std::vector<Particle> particles, const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType) :
        relativePositionInDomain(relativePositionInDomain), particles(std::move(particles)), position(position), cellType(cellType) {
    calculateBoundaries();
}

Cell::Cell(const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType) :
        relativePositionInDomain(relativePositionInDomain), position(position), cellType(cellType) {
    calculateBoundaries();
}

Cell::Cell() {

}

int Cell::getCellType() const {
    return cellType;
}

const std::array<double, 3> &Cell::getPosition() const {
    return position;
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

bool Cell::particleLiesInCell(Particle &p) {
    if (p.getX()[0] < position[0] || p.getX()[0] > position[0] + sizeX){
        return false;
    }
    if (p.getX()[1] < position[1] || p.getX()[1] > position[1] + sizeY){
        return false;
    }
    if (p.getX()[2] < position[2] || p.getX()[2] > position[2] + sizeZ){
        return false;
    }
    return true;
}

const std::array<int, 3> &Cell::getRelativePositionInDomain() const {
    return relativePositionInDomain;
}

Cell::Cell(std::vector<Particle> particles, const std::array<double, 3> &position, int cellType) :
        particles(std::move(particles)), position(position), cellType(cellType) {
    calculateBoundaries();
}


Cell::Cell(const std::array<double, 3> &position, int cellType) :
        position(position), cellType(cellType) {
    calculateBoundaries();
}

void Cell::setRelativePositionInDomain(const std::array<int, 3> &relativePositionInDomain) {
    Cell::relativePositionInDomain = relativePositionInDomain;
    calculateBoundaries();
}

void Cell::calculateBoundaries() {
    xBoundary = position[0] + sizeX;
    yBoundary = position[1] + sizeY;
    zBoundary = position[2] + sizeZ;

}

void Cell::reflectXtoRightCell(const std::array<double, 3> &pointWhichShouldBeReflected,
                               std::array<double, 3> &resultPoint) {
    resultPoint[0] = pointWhichShouldBeReflected[0] + 2 * (xBoundary - pointWhichShouldBeReflected[0]);
    resultPoint[1] = pointWhichShouldBeReflected[1];
    resultPoint[2] = pointWhichShouldBeReflected[2];
}

void Cell::reflectXtoLeftCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint) {
    resultPoint[0] = pointWhichShouldBeReflected[0] + 2 * (position[0] - pointWhichShouldBeReflected[0]);
    resultPoint[1] = pointWhichShouldBeReflected[1];
    resultPoint[2] = pointWhichShouldBeReflected[2];
}

void
Cell::reflectYtoTopCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint) {
    resultPoint[0] = pointWhichShouldBeReflected[0];
    resultPoint[1] = pointWhichShouldBeReflected[1] + 2 * (yBoundary - pointWhichShouldBeReflected[1]);
    resultPoint[2] = pointWhichShouldBeReflected[2];
}

void Cell::reflectYtoBottomCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint) {
    resultPoint[0] = pointWhichShouldBeReflected[0];
    resultPoint[1] = pointWhichShouldBeReflected[1] + 2 * (position[1] - pointWhichShouldBeReflected[1]);
    resultPoint[2] = pointWhichShouldBeReflected[2];
}

void Cell::reflectZtoFrontCell(const std::array<double, 3> &pointWhichShouldBeReflected,
                               std::array<double, 3> &resultPoint) {
    resultPoint[0] = pointWhichShouldBeReflected[0];
    resultPoint[1] = pointWhichShouldBeReflected[1];
    resultPoint[2] = pointWhichShouldBeReflected[2] + 2 * (zBoundary - pointWhichShouldBeReflected[2]);
}

void
Cell::reflectZtoBackCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint) {
    resultPoint[0] = pointWhichShouldBeReflected[0];
    resultPoint[1] = pointWhichShouldBeReflected[1];
    resultPoint[2] = pointWhichShouldBeReflected[2] + 2 * (position[2] - pointWhichShouldBeReflected[2]);
}

const int Cell::getInnerCellType() {
    return INNER_CELL;
}

const int Cell::getBoundaryCellType() {
    return BOUNDARY_CELL;
}

const int Cell::getHaloCellType() {
    return HALO_CELL;
}


