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

    /**
     * @brief creates all ghost particles and adds them to the simulation process so that the
     * periodic boundary has the right behavior
     */
    void insertGhostParticles();

    void reflectPositionToGhostLeftX(std::array<double, 3> &position);

    void reflectPositionToGhostTopY(std::array<double, 3> &position);

    void reflectPositionToGhostBottomY(std::array<double, 3> &position);

    void reflectPositionToGhostFrontZ(std::array<double, 3> &position);

    void reflectPositionToGhostBackZ(std::array<double, 3> &position);
};


#endif //PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H
