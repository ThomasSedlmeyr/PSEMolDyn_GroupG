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

    public:
        /**
         * @brief is used for debugging. When it is set to true the ghost particles were not deleted
         */
        static bool isDebug;

        /**
         * @brief is set in the BoundaryConditionContainer. It is set to true if the right and left side are
         * PeriodicBoundaryConditions
         */
        static bool isRightPeriodic;

        /**
         * @brief is set in the BoundaryConditionContainer. It is set to true if the top and bottom side are
         * PeriodicBoundaryConditions
         */
        static bool isBottomPeriodic;

        /**
         * @brief The constructor for the PeriodicBoundaryCondition
         * @param conditionType the type of condition
         * @param side the side where we have a periodic boundary condition. Please make sure that the opposite
         * side is also from the type PeriodicBoundaryCondition
         */
        PeriodicBoundaryCondition2D(int conditionType, int side);

        void calculateBoundaryCondition() override;

        void doWorkAfterCalculationStep() override;

        /**
         * @brief This method is used for inserting the correct GhostParticles in the correct HaloCells for every
         * particle in the boundary area.
         */
        void insertGhostParticles();

        /**
         * @brief Reflects a particle, which is in the left boundary area, to the right halo area.
         * @param position the position which should be reflected
         */
        inline void reflectPositionToGhostRightX(std::array<double, 3> &position);

        /**
         * @brief Reflects a particle, which is in the right boundary area, to the left halo area.
         * @param position the position which should be reflected
         */
        inline void reflectPositionToGhostLeftX(std::array<double, 3> &position);

        /**
         * @brief Reflects a particle, which is in the bottom boundary area, to the top halo area.
         * @param position the position which should be reflected
         */
        inline void reflectPositionToGhostTopY(std::array<double, 3> &position);

        /**
         * @brief Reflects a particle, which is in the top boundary area, to the bottom halo area.
         * @param position the position which should be reflected
         */
        inline void reflectPositionToGhostBottomY(std::array<double, 3> &position);
    };

}

#endif //PSEMOLDYN_GROUPG_PERIODICBOUNDARYCONDITION_H
