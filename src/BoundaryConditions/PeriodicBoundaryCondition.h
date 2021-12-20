//
// Created by thomas on 16.12.21.
//

#ifndef PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H
#define PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H


#include "BoundaryCondition.h"

class PeriodicBoundaryCondition : public BoundaryCondition {

private:
    void setNeighbourCell(Cell *cell);

    void addAdditionalNeighbours();

    inline void reflectPositionToGhostRightX(std::array<double, 3> &position);

public:
    static bool isDebug;

    PeriodicBoundaryCondition(int conditionType, int side);

    void calculateBoundaryCondition() override;

    void doWorkAfterCalculationStep() override;

    void insertGhostParticles();

};


#endif //PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H
