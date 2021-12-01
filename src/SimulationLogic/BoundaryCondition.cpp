//
// Created by thomas on 30.11.21.
//

#include "BoundaryCondition.h"

#include <utility>

void BoundaryCondition::calculateBoundaryCondition() {
    for (int i = 0; i < specificBoundaryCells.size(); i++) {
        //calculateBoundaryConditionForCell(specificBoundaryCells[i]);
    }
}

inline void BoundaryCondition::reflectPointAtX(std::array<double, 3>& point, double xPosition) {
    point[0] += 2*(xPosition-point[0]);
}

inline void BoundaryCondition::reflectPointAtY(std::array<double, 3>& point, double yPosition) {
    point[1] += 2*(yPosition-point[1]);
}

inline void BoundaryCondition::reflectPointAtZ(std::array<double, 3>& point, double zPosition) {
    point[2] += 2*(zPosition-point[2]);
}

void BoundaryCondition::setSpecificCells() {
    switch (side) {
        case FRONT:
            setSpecificCells(std::array<int, 3>{0,0,1}, numberCellsInZ-1, allHaloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0,0,1}, numberCellsInZ-2, allBoundaryCells, specificBoundaryCells);
            break;
        case RIGHT:
            setSpecificCells(std::array<int, 3>{1,0,0}, numberCellsInX-1, allHaloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{1,0,0}, numberCellsInX-2, allBoundaryCells, specificBoundaryCells);
            break;
        case BACK:
            setSpecificCells(std::array<int, 3>{0,0,1}, 0, allHaloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0,0,1}, 1, allBoundaryCells, specificBoundaryCells);
            break;
        case LEFT:
            setSpecificCells(std::array<int, 3>{1,0,0}, 0, allHaloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{1,0,0}, 1, allBoundaryCells, specificBoundaryCells);
            break;
        case TOP:
            setSpecificCells(std::array<int, 3>{0,1,0}, numberCellsInY-1, allHaloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0,1,0}, numberCellsInY-2, allBoundaryCells, specificBoundaryCells);
            break;
        case BOTTOM:
            setSpecificCells(std::array<int, 3>{0,1,0}, 0, allHaloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0,1,0}, 0, allBoundaryCells, specificBoundaryCells);
            break;
    }
}

void BoundaryCondition::setSpecificCells(std::array<int, 3> relativePositionMask, int relativePositionValue,
                                         std::vector<Cell *>& cells, std::vector<Cell*> matchingCells) {
    std::array<int, 3> vector{};
    for (auto cell : cells) {
        vector[0] = cell->getRelativePositionInDomain()[0]*relativePositionMask[0];
        vector[1] = cell->getRelativePositionInDomain()[1]*relativePositionMask[1];
        vector[2] = cell->getRelativePositionInDomain()[2]*relativePositionMask[2];
        double sum = vector[0] + vector[1] + vector[2];

        if(relativePositionValue == sum){
            matchingCells.push_back(cell);
        }
    }
}

BoundaryCondition::BoundaryCondition(int conditionType, int side, std::vector<Cell *> allBoundaryCells,
                                     std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY,
                                     int numberCellsInZ) : conditionType(conditionType), side(side),
                                                           allBoundaryCells(std::move(allBoundaryCells)),
                                                           allHaloCells(std::move(allHaloCells)), numberCellsInX(numberCellsInX),
                                                           numberCellsInY(numberCellsInY),
                                                           numberCellsInZ(numberCellsInZ) {
    setSpecificCells();
}

BoundaryCondition::BoundaryCondition() {}
