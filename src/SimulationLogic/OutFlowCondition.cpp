//
// Created by thomas on 30.11.21.
//

#include "OutFlowCondition.h"

void OutFlowCondition::calculateBoundaryCondition() {
    for (int i = 0; i < specificHaloCells.size(); ++i) {
        specificHaloCells[i]->getParticles().clear();
    }
}


OutFlowCondition::OutFlowCondition(int conditionType, int side) : BoundaryCondition(conditionType, side) {

}

void OutFlowCondition::doWorkAfterCalculationStep() {

}
