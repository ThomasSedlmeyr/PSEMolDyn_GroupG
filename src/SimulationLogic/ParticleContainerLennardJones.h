//
// Created by thomas on 24.11.21.
//

#ifndef PSEMOLDYN_GROUPG_PARTICLECONTAINERLENNARDJONES_H
#define PSEMOLDYN_GROUPG_PARTICLECONTAINERLENNARDJONES_H


#include <vector>
#include <memory>
#include "Cell.h"

class ParticleContainerLennardJones {
    /**
     * @brief all cells of the domain inner-, boundary-, halo-cells
     */
private:
    std::vector<Cell> cells;
    //std::vector<std::unique_ptr<Cell>> boundaryCells;
    //std::vector<std::unique_ptr<Cell>> haloCells;
    //std::vector<std::unique_ptr<Cell>> innerCells;
    std::vector<Cell *> boundaryCells;
    std::vector<Cell *> haloCells;
    std::vector<Cell *> innerCells;

    int currentIndexInCells = 0;

    int currentIndexHaloCells = 0;
    int currentIndexBoundaryCells = 0;
    int currentIndexInnerCells = 0;

    double domainSizeX;
    double domainSizeY;
    double domainSizeZ;

    int numberCellsX;
    int numberCellsY;
    int numberCellsZ;

    double cutOffRadius;

    std::array<double, 3> currentPosition;

    /**
     * The left front side Corner of the domain the haloCells are excluded
     * in the most common cases this position is (0,0,0)
     */
    std::array<double, 3> domainStartPosition;

private:
    void createCells();

    void cellsToXYZ();

    void buildOneRowInXdirection(int numberStonesInXdirection, int cellType);

    void setDimensionsOfCellPointerVectors();

    void addSingleHaloCell();

    void buildHaloSlice();

    void buildHaloAndBoundarySlice();

    void buildStandardLine();

    void addSingleBoundaryCell();

    void buildStandardSlice();

    void buildFullLineHaloCells();

    void buildLineOneHaloMultipleBoundariesOneHalo();

    std::array<int, 26> getNeighbourIndexes();

    std::array<int, 26> getNeighbourIndexes(int index);

    int movePositionsInX(int index, int numberOfPositions);

    int movePositionsInY(int index, int numberPositionsInY);

    int movePositionsInZ(int index, int numberPositionsInZ);
};


#endif //PSEMOLDYN_GROUPG_PARTICLECONTAINERLENNARDJONES_H
