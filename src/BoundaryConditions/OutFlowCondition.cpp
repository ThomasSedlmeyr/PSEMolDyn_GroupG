//
// Created by thomas on 30.11.21.
//

#include "OutFlowCondition.h"

void OutFlowCondition::calculateBoundaryCondition() {
    for (auto &specificHaloCell : specificHaloCells) {
        specificHaloCell->getParticles().clear();
    }
}


OutFlowCondition::OutFlowCondition(int conditionType, int side) : BoundaryCondition(conditionType, side) {

}

void OutFlowCondition::doWorkAfterCalculationStep() {
}
