//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_BETTERREFLECTINGCONDITION_H
#define PSEMOLDYN_GROUPG_BETTERREFLECTINGCONDITION_H


#include "BoundaryCondition.h"

class BetterReflectingCondition : public BoundaryCondition {
public:
    BetterReflectingCondition(int conditionType, int side);

    void calculateBoundaryCondition() override;

    /**
     * @brief Calculates the boundary condition for one cell. The particles which are in the halo cells were reflected to the
     * inside  of the domain. Also the velocity component that caused the leakage from the domain, will be inverted. With this
     * procedure we can achieve the equality of the entry angle to the reflection angle.
     * @param cell The cell for which this specific boundary should be calculated.
     */
    void calculateBoundaryConditionForCell(Cell *cell);

    void doWorkAfterCalculationStep() override;
};


#endif //PSEMOLDYN_GROUPG_BETTERREFLECTINGCONDITION_H
