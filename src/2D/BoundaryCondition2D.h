//
// Created by thomas on 30.11.21.
//

#pragma once

#include <vector>
#include "SimulationLogic/Cell.h"

namespace twoD{

    class BoundaryCondition2D {

    protected:
        /**
         * @brief The type of the condition
         */
        int conditionType;

        /**
         * @brief The side were the condition should be applied
         */
        int side;

        /**
         * @brief The boundary cells on which the collision should be applied
         */
        std::vector<Cell *> specificBoundaryCells;

        /**
         * @brief The halo cells on which the collision should be applied
         */
        std::vector<Cell *> specificHaloCells;

    public:
        /**
         * @brief constant value describing the OUTFLOW_TYPE
         */
        static const int OUTFLOW_TYPE = 1;

        /**
         * @brief constant value describing the REFLECTING_TYPE
         */
        static const int REFLECTING_TYPE = 2;

        /**
         * @brief constant value describing the BETTER_REFLECTION_TYPE
         */
        static const int BETTER_REFLECTION_TYPE = 3;

        [[nodiscard]] const std::vector<Cell *> &getSpecificBoundaryCells() const;

        [[nodiscard]] const std::vector<Cell *> &getSpecificHaloCells() const;

        /**
         * @brief the types which describe the different sides on which the boundary conditions can be applied
         */
        static const int RIGHT = 1;
        static const int LEFT = 2;
        static const int TOP = 3;
        static const int BOTTOM = 4;

        /**
         * @brief apply the boundary condition
         */
        virtual void calculateBoundaryCondition() = 0;

        /**
         * @brief If after the collision some work has to be done, this can be done in this methode
         * For example: Deleting the ghost particles
         */
        virtual void doWorkAfterCalculationStep() = 0;

        BoundaryCondition2D();

        /**
         * Constructor for the BoundaryCondition
         * @param conditionType the type of the condition
         * @param side the side on which the boundary condition should be invoked
         */
        BoundaryCondition2D(int conditionType, int side);

    private:
        /**
         * @brief Sets the right specific cells (specificHaloCells, specificBoundaryCells) according to the side on which
         * the boundary condition should be applied
         */
        void setSpecificCells();

    protected:

        /**
         * @brief This method is a helper method for the setSpecificCells(). It uses the scalar product to extract the correct row of
         * cells and append these new cells to the vector matchingCells
         * @param relativePositionMask the mask which defines the relative position of the cell
         * @param relativePositionValue  the position of the row (where 0 stands for halo-row and 1 for boundary-row)
         * @param cell a reference to the vector containing all cells
         * @param matchingCells the reference to the vector at which the extracted cell should be append
         */
        void
        setSpecificCells(std::array<int, 2> relativePositionMask, int relativePositionValue, std::vector<Cell *> &cells,
                         std::vector<Cell *> &matchingCells);

        /**
         *@brief deletes all particles in the halo cells
         */
        void deleteAllParticlesInHaloCells();
    };
}
