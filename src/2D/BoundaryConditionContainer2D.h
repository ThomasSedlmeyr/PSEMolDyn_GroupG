//
// Created by thomas on 30.11.21.
//

#pragma once
#include <array>
#include <vector>
#include <SimulationLogic/Cell.h>
#include "BoundaryCondition2D.h"
namespace twoD {
    class BoundaryConditionContainer2D {

    private:
        /**
         * @brief all boundaryCells of the domain
         */
        std::vector<Cell *> allBoundaryCells{};

        /**
         * @brief all haloCells of the domain
         */
        std::vector<Cell *> allHaloCells{};

        /**
         * @brief the number of Cells in xDirection including the haloCells
         */
        int numberCellsInX{};

        /**
         * @brief the number of Cells in yDirection including the haloCells
         */
        int numberCellsInY{};

        /**
         * @brief the size of the domain
         * domainSize[0]: size in x-direction
         * domainSize[1]: size in y-direction
         * domainSize[2]: size in z-direction
         */
        std::array<double, 3> domainSize{};

        /**
         * @brief the six different conditions for every side of the domain
         * boundaryCondition[0]: right side
         * boundaryCondition[1]: left side
         * boundaryCondition[2]: top side
         * boundaryCondition[3]: bottom side
         */
        std::array<BoundaryCondition2D *, 4> boundaryConditions{};

    public:
        /**
         * @brief The constructor for the BoundaryConditionContainer
         * @param boundaryConditionTypes an array of size 6 which contains the different boundary condition types in the order:
         * front, right, back, left, top, bottom
         * @param numberCellsInX
         * @param numberCellsInY
         * @param numberCellsInZ
         */
        BoundaryConditionContainer2D(const std::array<int, 4> &boundaryConditionTypes, int numberCellsInX,
                                     int numberCellsInY,
                                     std::array<double, 3> domainSize);

        /**
         *@brief Calculates the boundary Conditions for every side of the domain
         */
        void calculateBoundaryConditions();

        /**
         * @brief if some boundaries need to do some work after the calculation, this method calls for every boundary condition
         * the method doWorkAfterCalculation
         */
        void doWorkAfterCalculationStep();

        [[nodiscard]] const std::array<BoundaryCondition2D *, 4> &getBoundaryConditions() const;
    };
}