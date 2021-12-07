//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_BOUNDARYCONDITIONCONTAINER_H
#define PSEMOLDYN_GROUPG_BOUNDARYCONDITIONCONTAINER_H

#include <array>
#include "BoundaryCondition.h"

class BoundaryConditionContainer {

private:
    /**
     * @brief all boundaryCells of the domain
     */
    std::vector<Cell *> allBoundaryCells{};

    /**
     * @brief all haloCells of the domain
     */
    std::vector<Cell *> allHaloCells{};

    int numberCellsInX{};
    int numberCellsInY{};
    int numberCellsInZ{};

    /**
     * @brief the size of the domain
     * domainSize[0]: size in x-direction
     * domainSize[1]: size in y-direction
     * domainSize[2]: size in z-direction
     */
    std::array<double, 3> domainSize{};

    /**
     * @brief the six different conditions for every side of the domain
     * boundaryCondition[0]: front side
     * boundaryCondition[1]: right side
     * boundaryCondition[2]: back side
     * boundaryCondition[3]: left side
     * boundaryCondition[4]: top side
     * boundaryCondition[5]: bottom side
     */
    std::array<BoundaryCondition *, 6> boundaryConditions{};

public:
    /**
     * @brief The constructor for the BoundaryConditionContainer
     * @param boundaryConditionTypes an array of size 6 which contains the different boundary condition types in the order:
     * front, right, back, left, top, bottom
     * @param allBoundaryCells all boundary cells of the domain
     * @param allHaloCells all halo cells of the domain
     * @param numberCellsInX
     * @param numberCellsInY
     * @param numberCellsInZ
     * @param domainSize the size of the domain
     */
    BoundaryConditionContainer(const std::array<int, 6> &boundaryConditionTypes, std::vector<Cell *> allBoundaryCells,
                               std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY,
                               int numberCellsInZ, const std::array<double, 3> domainSize);

    /**
     *@brief Calculates the boundary Conditions for every side of the domain
     */
    void calculateBoundaryConditions();

    /**
     * @brief if some boundaries need to do some work after the calculation, this method calls for every boundary condition
     * the method doWorkAfterCalculation
     */
    void doWorkAfterCalculationStep();

    [[nodiscard]] const std::array<BoundaryCondition *, 6> &getBoundaryConditions() const;
};


#endif //PSEMOLDYN_GROUPG_BOUNDARYCONDITIONCONTAINER_H
