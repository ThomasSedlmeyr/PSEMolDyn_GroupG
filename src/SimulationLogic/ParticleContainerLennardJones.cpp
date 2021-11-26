//
// Created by thomas on 24.11.21.
//

#include "ParticleContainerLennardJones.h"


void ParticleContainerLennardJones::createCells() {
    //Two is added because of the HaloCells
    numberCellsX = int(domainSizeX / cutOffRadius) + 2;
    numberCellsY = int(domainSizeY / cutOffRadius) + 2;
    numberCellsZ = int(domainSizeZ / cutOffRadius) + 2;

    cells.resize(numberCellsX * numberCellsY * numberCellsZ);


    Cell::sizeX = double(domainSizeX) / numberCellsX;
    Cell::sizeY = double(domainSizeY) / numberCellsY;
    Cell::sizeZ = double(domainSizeZ) / numberCellsZ;

    //The currentPosition has to be adapted according to the cell dimensions
    currentPosition = {domainStartPosition[0] - numberCellsX,
                       domainStartPosition[1] - numberCellsY,
                       domainStartPosition[2] + numberCellsZ};

    setDimensionsOfCellPointerVectors();


    buildHaloSlice();
    buildHaloAndBoundarySlice();
    for (int z = 0; z < numberCellsZ - 4; ++z) {
        buildStandardSlice();
    }
    buildHaloAndBoundarySlice();
    buildHaloSlice();
    //x Rechts
    //y hoch runter
    //z raus
}

void ParticleContainerLennardJones::buildStandardSlice() {
    double oldPositionY = currentPosition[1];
    //building the first line containing only halo cells
    buildFullLineHaloCells();
    buildLineOneHaloMultipleBoundariesOneHalo();
    for (int i = 0; i < numberCellsY - 4; ++i) {
        buildStandardLine();
    }
    buildLineOneHaloMultipleBoundariesOneHalo();
    buildFullLineHaloCells();
    //building the second line containing halo and boundary cells
    currentPosition[1] = oldPositionY;
    currentPosition[2] -= Cell::sizeZ;
}

void ParticleContainerLennardJones::buildStandardLine() {
    double oldPositionX = currentPosition[0];
    addSingleHaloCell();
    addSingleBoundaryCell();
    buildOneRowInXdirection(numberCellsX - 4, Cell::INNER_CELL);
    addSingleBoundaryCell();
    addSingleHaloCell();
    currentPosition[0] = oldPositionX;
    currentPosition[1] += Cell::sizeY;
}

void ParticleContainerLennardJones::addSingleHaloCell() {
    cells[currentIndexInCells] = Cell(currentPosition, Cell::HALO_CELL);
    haloCells[currentIndexHaloCells] = &cells[currentIndexInCells];
    currentIndexInCells++;
    currentIndexHaloCells++;
    currentPosition[0] += Cell::sizeX;
}

void ParticleContainerLennardJones::addSingleBoundaryCell() {
    cells[currentIndexInCells] = Cell(currentPosition, Cell::HALO_CELL);
    haloCells[currentIndexBoundaryCells] = &cells[currentIndexInCells];
    currentIndexInCells++;
    currentIndexBoundaryCells++;
    currentPosition[0] += Cell::sizeX;
}

//Important: This simulation changes the xPostion of the currentPosition
void ParticleContainerLennardJones::buildOneRowInXdirection(int numberStonesInXdirection, int cellType) {
    for (int x = 0; x < numberStonesInXdirection; x++) {
        cells[currentIndexInCells] = Cell(currentPosition, cellType);
        currentPosition[0] += Cell::sizeX;

        //insert new cell into the right pointer array
        switch (cellType) {
            case Cell::INNER_CELL:
                innerCells[currentIndexInnerCells] = &cells[currentIndexInCells];
                currentIndexInnerCells++;
                break;
            case Cell::HALO_CELL:
                boundaryCells[currentIndexHaloCells] = &cells[currentIndexInCells];
                currentIndexHaloCells++;
                break;
            case Cell::BOUNDARY_CELL:
                innerCells[currentIndexHaloCells] = &cells[currentIndexInCells];
                currentIndexHaloCells++;
                break;
        }
        currentIndexInCells++;
    }
}

void ParticleContainerLennardJones::setDimensionsOfCellPointerVectors() {
    boundaryCells.resize(
            (numberCellsX - 2) * (numberCellsZ - 2) * 2 + (numberCellsX - 2) * ((numberCellsY - 2) - 2) * 2 +
            (numberCellsZ - 4) * (numberCellsY - 4) * 2);
    haloCells.resize(numberCellsX * numberCellsZ * 2 + numberCellsX * (numberCellsY - 2) * 2 +
                     (numberCellsZ - 2) * (numberCellsY - 2) * 2);;
    innerCells.resize((numberCellsX - 4) * (numberCellsY - 4) * (numberCellsZ - 4));;
}

void ParticleContainerLennardJones::buildHaloSlice() {
    double oldPositionX = currentPosition[0];
    double oldPositionY = currentPosition[1];
    //building the first slice which consists only out of halo cells
    for (int i = 0; i < numberCellsY; i++) {
        buildFullLineHaloCells();
    }
    currentPosition[0] = oldPositionX;
    currentPosition[1] = oldPositionY;
    currentPosition[2] -= Cell::sizeZ;

}

void ParticleContainerLennardJones::buildHaloAndBoundarySlice() {
    double oldPositionY = currentPosition[1];
    //building the first line containing only halo cells
    buildFullLineHaloCells();
    for (int i = 0; i < numberCellsY - 2; ++i) {
        buildLineOneHaloMultipleBoundariesOneHalo();
    }
    buildFullLineHaloCells();
    //building the second line containing halo and boundary cells
    currentPosition[1] = oldPositionY;
    currentPosition[2] -= Cell::sizeZ;
}

void ParticleContainerLennardJones::buildFullLineHaloCells() {
    double oldPositionX = currentPosition[0];
    buildOneRowInXdirection(numberCellsX, Cell::HALO_CELL);
    currentPosition[0] = oldPositionX;
    currentPosition[1] += Cell::sizeY;
}

void ParticleContainerLennardJones::buildLineOneHaloMultipleBoundariesOneHalo() {
    double oldPositionX = currentPosition[0];
    addSingleHaloCell();
    buildOneRowInXdirection(numberCellsX - 2, Cell::BOUNDARY_CELL);
    addSingleHaloCell();
    currentPosition[0] = oldPositionX;
    currentPosition[1] += Cell::sizeY;
}

std::array<int, 26> ParticleContainerLennardJones::getNeighbourIndexes(int index) {
    std::array<int, 26> resultArray{};
    int numbersCellsPerSlice = numberCellsX * numberCellsY;
    //z-1
    resultArray[0] = index - numbersCellsPerSlice;

    resultArray;
}

int ParticleContainerLennardJones::movePositionsInX(int index, int numberPositionsInX) {
    return index + numberPositionsInX;
}

int ParticleContainerLennardJones::movePositionsInY(int index, int numberPositionsInY) {
    return index + numberCellsX * numberPositionsInY;
}

int ParticleContainerLennardJones::movePositionsInZ(int index, int numberPositionsInZ) {
    return index + numberCellsX * numberCellsY * numberPositionsInZ;
}