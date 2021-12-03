//
// Created by thomas on 01.12.21.
//

#ifndef PSEMOLDYN_GROUPG_LOOPCONDITION_H
#define PSEMOLDYN_GROUPG_LOOPCONDITION_H


#include "BoundaryCondition.h"

class LoopCondition : public BoundaryCondition{
    void calculateBoundaryCondition() override;
};


#endif //PSEMOLDYN_GROUPG_LOOPCONDITION_H
