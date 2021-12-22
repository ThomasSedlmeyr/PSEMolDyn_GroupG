//
// Created by thomas on 16.12.21.
//

#ifndef PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H
#define PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H


#include "BoundaryCondition2D.h"
namespace twoD {
    class PeriodicBoundaryCondition2D : public BoundaryCondition2D {

    private:
        void setNeighbourCell(Cell *cell);

        void addAdditionalNeighbours();

        inline void reflectPositionToGhostRightX(std::array<double, 3> &position);

    public:
        static bool isDebug;

        PeriodicBoundaryCondition2D(int conditionType, int side);

        void calculateBoundaryCondition() override;

        void doWorkAfterCalculationStep() override;

        void insertGhostParticles();

        void reflectPositionToGhostLeftX(std::array<double, 3> &position);

        void reflectPositionToGhostTopY(std::array<double, 3> &position);

        void reflectPositionToGhostBottomY(std::array<double, 3> &position);

        void reflectPositionToGhostFrontZ(std::array<double, 3> &position);

        void reflectPositionToGhostBackZ(std::array<double, 3> &position);
    };

}

#endif //PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H
