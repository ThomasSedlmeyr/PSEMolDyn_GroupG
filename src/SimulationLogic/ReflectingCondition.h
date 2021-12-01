//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H
#define PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H


#include <vector>
#include "Particle.h"
#include "Cell.h"
#include "BoundaryCondition.h"

class ReflectingCondition : public BoundaryCondition {

private:
    ReflectingCondition(int conditionType, int side, std::vector<Cell *> allBoundaryCells,
                        std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY, int numberCellsInZ);

    double h;

protected:
    std::vector<Particle*> counterParticles;
    void calculateBoundaryConditionForCell(Cell* cell);
};


#endif //PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H
