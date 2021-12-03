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

public:
    ReflectingCondition(int conditionType, int side);
    double h;

protected:
    std::vector<Particle*> counterParticles;
    void calculateBoundaryCondition() override;

private:
    void calculateBoundaryConditionForCell(Cell *cell);
};


#endif //PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H
