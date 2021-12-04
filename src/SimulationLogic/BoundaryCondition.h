//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_BOUNDARYCONDITION_H
#define PSEMOLDYN_GROUPG_BOUNDARYCONDITION_H


#include <vector>
#include "Cell.h"

class BoundaryCondition {

protected:

    int conditionType;
    int side;
    std::vector<Cell *> specificBoundaryCells;
    std::vector<Cell *> specificHaloCells;

public:
    static const int OUTFLOW_TYPE = 1;

    const std::vector<Cell *> &getSpecificBoundaryCells() const;

    const std::vector<Cell *> &getSpecificHaloCells() const;

    static const int REFLECTING_TYPE = 2;


    static const int FRONT = 1;
    static const int RIGHT = 2;
    static const int BACK = 3;
    static const int LEFT = 4;
    static const int TOP = 5;
    static const int BOTTOM = 6;

    //virtual void calculateBoundaryConditionForCell(Cell* cell) = 0;

    virtual void calculateBoundaryCondition() = 0;
    virtual void doWorkAfterCalculationStep() = 0;
private:

    void setSpecificCells();

public:
    BoundaryCondition();
    BoundaryCondition(int conditionType, int side);

protected:
    void reflectPointAtX(std::array<double, 3>& point, double xPosition);
    void reflectPointAtY(std::array<double, 3>& point, double yPosition);
    void reflectPointAtZ(std::array<double, 3>& point, double zPosition);

    void
    setSpecificCells(std::array<int, 3> relativePositionMask, int relativePositionValue, std::vector<Cell *> &cells,
                     std::vector<Cell *> &matchingCells);

    void deleteAllParticlesInHaloCells();
};


#endif //PSEMOLDYN_GROUPG_BOUNDARYCONDITION_H
