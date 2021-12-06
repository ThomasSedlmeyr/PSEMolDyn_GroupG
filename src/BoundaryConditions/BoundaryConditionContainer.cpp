//
// Created by thomas on 30.11.21.
//

#include "BoundaryConditionContainer.h"
#include "BoundaryConditions/OutFlowCondition.h"
#include "BoundaryConditions/ReflectingCondition.h"
#include "BoundaryConditions/BetterReflectingCondition.h"

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
BoundaryConditionContainer::BoundaryConditionContainer(const std::array<int, 6> &boundaryConditionTypes,
                                                       std::vector<Cell *> allBoundaryCells,
                                                       std::vector<Cell *> allHaloCells, int numberCellsInX,
                                                       int numberCellsInY, int numberCellsInZ,
                                                       const std::array<double, 3> domainSize) :
        allBoundaryCells(std::move(allBoundaryCells)),
        allHaloCells(std::move(allHaloCells)),
        numberCellsInX(numberCellsInX),
        numberCellsInY(numberCellsInY),
        numberCellsInZ(numberCellsInZ),
        domainSize(domainSize) {

    for (std::size_t i = 0; i < boundaryConditionTypes.size(); i++) {
        switch (boundaryConditionTypes[i]) {
            case BoundaryCondition::OUTFLOW_TYPE:
                boundaryConditions[i] = new OutFlowCondition(BoundaryCondition::OUTFLOW_TYPE, i + 1);
                break;
            case BoundaryCondition::REFLECTING_TYPE:
                boundaryConditions[i] = new ReflectingCondition(BoundaryCondition::REFLECTING_TYPE, i + 1, domainSize);
                break;
            case BoundaryCondition::REFLECTIONANGEL_TYPE:
                boundaryConditions[i] = new BetterReflectingCondition(BoundaryCondition::REFLECTIONANGEL_TYPE, i + 1);
        }
    }
}

const std::array<BoundaryCondition *, 6> &BoundaryConditionContainer::getBoundaryConditions() const {
    return boundaryConditions;
}

void BoundaryConditionContainer::doWorkAfterCalculationStep(){
    for (auto b : boundaryConditions) {
        b->doWorkAfterCalculationStep();
    }
}