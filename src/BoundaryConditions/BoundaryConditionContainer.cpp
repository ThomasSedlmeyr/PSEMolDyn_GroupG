//
// Created by thomas on 30.11.21.
//

#include "BoundaryConditionContainer.h"
#include "BoundaryConditions/OutFlowCondition.h"
#include "BoundaryConditions/ReflectingCondition.h"
#include "BoundaryConditions/BetterReflectingCondition.h"
#include "XML_Parser/XMLParser.h"
#include "PeriodicBoundaryCondition.h"

#include <utility>



BoundaryConditionContainer::BoundaryConditionContainer(const std::array<int, 6> &boundaryConditionTypes,
                                                       int numberCellsInX,
                                                       int numberCellsInY,
                                                       int numberCellsInZ, std::array<double, 3> domainSize) :
        numberCellsInX(numberCellsInX),
        numberCellsInY(numberCellsInY),
        numberCellsInZ(numberCellsInZ),
        domainSize(domainSize){

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
                break;
            case BoundaryCondition::PERIODIC_BOUNDARY_TYPE:
                boundaryConditions[i] = new PeriodicBoundaryCondition(BoundaryCondition::PERIODIC_BOUNDARY_TYPE, i + 1);
        }
    }
    //front, right, back, left, top, bottom
    if(boundaryConditionTypes[0] == BoundaryCondition::PERIODIC_BOUNDARY_TYPE){
        PeriodicBoundaryCondition::isFrontPeriodic = true;
    }
    if(boundaryConditionTypes[1] == BoundaryCondition::PERIODIC_BOUNDARY_TYPE){
        PeriodicBoundaryCondition::isRightPeriodic = true;
    }
    if(boundaryConditionTypes[5] == BoundaryCondition::PERIODIC_BOUNDARY_TYPE){
        PeriodicBoundaryCondition::isBottomPeriodic = true;
    }
}

void BoundaryConditionContainer::calculateBoundaryConditions() {
    for (auto &boundaryCondition : boundaryConditions) {
        boundaryCondition->calculateBoundaryCondition();
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