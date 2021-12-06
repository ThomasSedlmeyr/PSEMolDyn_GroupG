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

    void calculateBoundaryConditionForCell(Cell *cell);

    void doWorkAfterCalculationStep() override;
};


#endif //PSEMOLDYN_GROUPG_BETTERREFLECTINGCONDITION_H
