//
// Created by thomas on 24.11.21.
//

#include <outputWriter/XYZWriter.h>
#include <outputWriter/VTKWriter.h>
#include <iostream>
#include "ParticleContainerLennardJones.h"


void ParticleContainerLennardJones::createCells() {
    numberCellsX = int(domainSizeX / cutOffRadius);
    numberCellsY = int(domainSizeY / cutOffRadius);
    numberCellsZ = int(domainSizeZ / cutOffRadius);

    Cell::sizeX = double(domainSizeX) / numberCellsX;
    Cell::sizeY = double(domainSizeY) / numberCellsY;
    Cell::sizeZ = double(domainSizeZ) / numberCellsZ;

    //Two is added because of the HaloCells
    numberCellsX += 2;
    numberCellsY += 2;
    numberCellsZ += 2;

    cells.resize(numberCellsX * numberCellsY * numberCellsZ);

    //The currentPosition has to be adapted according to the cell dimensions
    currentPosition = {domainStartPosition[0] - Cell::sizeX,
                       domainStartPosition[1] - Cell::sizeY,
                       domainStartPosition[2] + Cell::sizeZ};

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
    cells[currentIndexInCells] = Cell(currentPosition, Cell::BOUNDARY_CELL);
    boundaryCells[currentIndexBoundaryCells] = &cells[currentIndexInCells];
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
                haloCells[currentIndexHaloCells] = &cells[currentIndexInCells];
                currentIndexHaloCells++;
                break;
            case Cell::BOUNDARY_CELL:
                boundaryCells[currentIndexBoundaryCells] = &cells[currentIndexInCells];
                currentIndexBoundaryCells++;
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

std::array<int, 26> ParticleContainerLennardJones::getNeighbourIndices(int index) {
    std::array<int, 26> resultArray{};
    int currentXIndex;
    int currentYIndex;
    int currentNeighbourIndex;
    int counter = 0;
    for (int i = -1; i < 2; ++i) {
        //move by i in x direction
        currentXIndex = movePositionsInX(index, i);
        for (int j = -1; j < 2; ++j) {
            //move by j in y direction
            currentYIndex = movePositionsInY(currentXIndex, j);
            for (int k = -1; k < 2; ++k) {
                if (i == 0 && j == 0 && k == 0){
                    continue;
                }
                //move by k in z direction
                currentNeighbourIndex = movePositionsInZ(currentYIndex, k);
                if (currentNeighbourIndex < 0 || currentNeighbourIndex > cells.size()){
                    currentNeighbourIndex = -1;
                }
                resultArray[counter] = currentNeighbourIndex;
                counter++;
            }
        }
    }
    return resultArray;
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

void ParticleContainerLennardJones::cellsToXYZ() {
    std::vector<Particle> linkedCellParticles;
    //std::vector<Particle> linkedCellParticles = std::vector<Particle>(cells.size());
    createCells();
    for (int i = 0; i < cells.size(); ++i) {
        linkedCellParticles.emplace_back(cells[i].getPosition(), std::array<double, 3>{1,1,1}, 100, cells[i].getCellType(),i);
    }
    //At this index we get an error in the VTKWriter
    std::cout << linkedCellParticles[21].getX()[1] << std::endl;
    VTKWriter writer = VTKWriter();
    writer.writeParticlesToFile("LinkedCells", 1, linkedCellParticles);
    std::cout << "Fertig" << std::endl;
}

ParticleContainerLennardJones::ParticleContainerLennardJones(double domainSizeX, double domainSizeY, double domainSizeZ,
                                                             double cutOffRadius,
                                                             const std::array<double, 3> &domainStartPosition)
        : domainSizeX(domainSizeX), domainSizeY(domainSizeY), domainSizeZ(domainSizeZ), cutOffRadius(cutOffRadius),
          domainStartPosition(domainStartPosition) {}

ParticleContainerLennardJones::ParticleContainerLennardJones() {}

const std::vector<Cell *> &ParticleContainerLennardJones::getBoundaryCells() const {
    return boundaryCells;
}

const std::vector<Cell *> &ParticleContainerLennardJones::getHaloCells() const {
    return haloCells;
}

const std::vector<Cell *> &ParticleContainerLennardJones::getInnerCells() const {
    return innerCells;
}

const std::vector<Cell>& ParticleContainerLennardJones::getCells() const {
    return cells;
}
