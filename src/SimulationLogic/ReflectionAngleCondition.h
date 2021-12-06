//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_REFLECTIONANGLECONDITION_H
#define PSEMOLDYN_GROUPG_REFLECTIONANGLECONDITION_H


#include "BoundaryCondition.h"

class ReflectionAngleCondition : public BoundaryCondition {
public:
    ReflectionAngleCondition(int conditionType, int side);

    void calculateBoundaryCondition() override;

    void calculateBoundaryConditionForCell(Cell *cell);

    void doWorkAfterCalculationStep() override;
};


#endif //PSEMOLDYN_GROUPG_REFLECTIONANGLECONDITION_H
