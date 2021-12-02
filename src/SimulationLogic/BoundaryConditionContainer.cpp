//
// Created by thomas on 30.11.21.
//

#include "BoundaryConditionContainer.h"
#include "OutFlowCondition.h"

#include <utility>

void BoundaryConditionContainer::calculateBoundaryConditions() {
    for(BoundaryCondition* boundary : boundaryConditions){
        boundary->calculateBoundaryCondition();
    }
}

BoundaryConditionContainer::BoundaryConditionContainer(int frontSide, int rightSide, int backSide, int leftSide,
                                                       int topSide, int bottomSide) {


}

BoundaryConditionContainer::BoundaryConditionContainer(int frontAndBackSide, int rightAndLeftSide,
                                                       int topAndBottomSide) {
    BoundaryConditionContainer(frontAndBackSide, rightAndLeftSide, frontAndBackSide, rightAndLeftSide, topAndBottomSide, topAndBottomSide);
}
//Very import the order of the types in boundaryConditionTypes has to be the same as the numerical oder of side types
//which were defined in the class BoundaryCondition.h
BoundaryConditionContainer::BoundaryConditionContainer(std::array<int, 6>& boundaryConditionTypes,
                                                       std::vector<Cell *> allBoundaryCells,
                                                       std::vector<Cell *> allHaloCells, int numberCellsInX,
                                                       int numberCellsInY, int numberCellsInZ) :
                                                       allBoundaryCells(std::move(allBoundaryCells)),
                                                       allHaloCells(std::move(allHaloCells)),
                                                       numberCellsInX(numberCellsInX),
                                                       numberCellsInY(numberCellsInY),
                                                       numberCellsInZ(numberCellsInZ) {
    boundaryConditions.reserve(6);
    for (int i = 0; i < boundaryConditionTypes.size(); i++) {
        switch(boundaryConditionTypes[i]){
            case BoundaryCondition::OUTFLOW_TYPE:
                boundaryConditions[i] = new OutFlowCondition(BoundaryCondition::OUTFLOW_TYPE, i+1, allBoundaryCells,
                                                         allHaloCells, numberCellsInX, numberCellsInY, numberCellsInZ);
                break;
            case BoundaryCondition::REFLECTING_TYPE:
                break;
        }
    }
}
