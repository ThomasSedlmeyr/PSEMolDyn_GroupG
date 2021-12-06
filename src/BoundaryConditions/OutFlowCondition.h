//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_OUTFLOWCONDITION_H
#define PSEMOLDYN_GROUPG_OUTFLOWCONDITION_H


#include "BoundaryCondition.h"

class OutFlowCondition : public BoundaryCondition{

protected:

    void calculateBoundaryCondition();


public:
    OutFlowCondition(int conditionType, int side);
    void doWorkAfterCalculationStep() override;
};


#endif //PSEMOLDYN_GROUPG_OUTFLOWCONDITION_H
