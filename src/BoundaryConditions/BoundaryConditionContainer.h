//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_BOUNDARYCONDITIONCONTAINER_H
#define PSEMOLDYN_GROUPG_BOUNDARYCONDITIONCONTAINER_H

#include <array>
#include "BoundaryCondition.h"

class BoundaryConditionContainer {

private:


    std::vector<Cell*> allBoundaryCells{};
    std::vector<Cell*> allHaloCells{};
    int numberCellsInX{};
    int numberCellsInY{};
    int numberCellsInZ{};
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
    std::array<BoundaryCondition*, 6> boundaryConditions{};
public:
    BoundaryConditionContainer(const std::array<int, 6> &boundaryConditionTypes, std::vector<Cell *> allBoundaryCells,
                               std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY,
                               int numberCellsInZ, const std::array<double, 3> domainSize);
public:
    /**
     * @brief Constructor which sets the boundary conditions for every side
     *
     * @param frontSide boundary condition for the front side
     * @param rightSide boundary condition for the right side
     * @param backSide boundary condition for the back side
     * @param leftSide boundary condition for the left side
     * @param topSide boundary condition for the top side
     * @param bottomSide condition for the bottom side
     */
    BoundaryConditionContainer(int frontSide, int rightSide, int backSide,
                               int leftSide, int topSide, int bottomSide);


    /**
     * @brief Constructor which sets the boundary conditions for one side and its opposite side
     *
     * @param frontAndBackSide
     * @param rightAndLeftSide
     * @param topAndBottomSide
     */
    BoundaryConditionContainer(int frontAndBackSide, int rightAndLeftSide, int topAndBottomSide);

    void calculateBoundaryConditions();

    void doWorkAfterCalculationStep();

    const std::array<BoundaryCondition *, 6> &getBoundaryConditions() const;
};


#endif //PSEMOLDYN_GROUPG_BOUNDARYCONDITIONCONTAINER_H
