//
// Created by thomas on 30.11.21.
//

#include "BoundaryConditionContainerTest.h"
#include "BoundaryConditions/OutFlowCondition.h"
#include "BoundaryConditions/ReflectingCondition.h"
#include "BoundaryConditions/BetterReflectingCondition.h"

#include <utility>

void BoundaryConditionContainer::calculateBoundaryConditions() {
    for (auto &boundaryCondition : boundaryConditions) {
        boundaryCondition->calculateBoundaryCondition();
    }
}


BoundaryConditionContainer::BoundaryConditionContainer(const std::array<int, 6> &boundaryConditionTypes,
                                                       int numberCellsInX,
                                                       int numberCellsInY,
                                                       int numberCellsInZ) :
        numberCellsInX(numberCellsInX),
        numberCellsInY(numberCellsInY),
        numberCellsInZ(numberCellsInZ) {

    for (std::size_t i = 0; i < boundaryConditionTypes.size(); i++) {
        switch (boundaryConditionTypes[i]) {
            case BoundaryCondition::OUTFLOW_TYPE:
                boundaryConditions[i] = new OutFlowCondition(BoundaryCondition::OUTFLOW_TYPE, i + 1);
                break;
            case BoundaryCondition::REFLECTING_TYPE:
                boundaryConditions[i] = new ReflectingCondition(BoundaryCondition::REFLECTING_TYPE, i + 1, domainSize);
                break;
            case BoundaryCondition::BETTER_REFLECTION_TYPE:
                boundaryConditions[i] = new BetterReflectingCondition(BoundaryCondition::BETTER_REFLECTION_TYPE, i + 1);
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