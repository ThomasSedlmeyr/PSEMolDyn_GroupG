//
// Created by thomas on 30.11.21.
//

#include "BoundaryConditionContainer.h"
#include "OutFlowCondition.h"
#include "ReflectingCondition.h"

#include <utility>

void BoundaryConditionContainer::calculateBoundaryConditions() {
    for (auto &boundaryCondition : boundaryConditions) {
        boundaryCondition->calculateBoundaryCondition();
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
                                                       int numberCellsInY, int numberCellsInZ, const std::array<double, 3> domainSize) :
                                                       allBoundaryCells(std::move(allBoundaryCells)),
                                                       allHaloCells(std::move(allHaloCells)),
                                                       numberCellsInX(numberCellsInX),
                                                       numberCellsInY(numberCellsInY),
                                                       numberCellsInZ(numberCellsInZ),
                                                       domainSize(domainSize){
    for (int i = 0; i < boundaryConditionTypes.size(); i++) {
        switch(boundaryConditionTypes[i]){
            case 1:
                boundaryConditions[i] = new OutFlowCondition(1, i+1);
                break;
            case 2:
                boundaryConditions[i] = new ReflectingCondition(2, i+1, domainSize);
                break;
        }
    }
}
