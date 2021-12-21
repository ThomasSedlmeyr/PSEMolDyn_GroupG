//
// Created by thomas on 30.11.21.
//

#include "OutFlowCondition2D.h"
namespace twoD {
    void OutFlowCondition2D::calculateBoundaryCondition() {
        for (auto &specificHaloCell: specificHaloCells) {
            specificHaloCell->getParticles().clear();
        }
    }


    OutFlowCondition2D::OutFlowCondition2D(int conditionType, int side) : BoundaryCondition2D(conditionType, side) {

    }

    void OutFlowCondition2D::doWorkAfterCalculationStep() {
    }
}