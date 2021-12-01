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
    OutFlowCondition(int conditionType, int side, std::vector<Cell *> allBoundaryCells,
                      std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY,
                      int numberCellsInZ);
};


#endif //PSEMOLDYN_GROUPG_OUTFLOWCONDITION_H
