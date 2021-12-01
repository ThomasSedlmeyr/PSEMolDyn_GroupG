//
// Created by thomas on 24.11.21.
//

#include <outputWriter/XYZWriter.h>
#include <outputWriter/VTKWriter.h>
#include <iostream>
#include <Visitors/ParticleCollector.h>
#include "ParticleContainerLinkedCells.h"
#include "utils/ArrayUtils.h"

ParticleContainerLinkedCells::ParticleContainerLinkedCells(double domainSizeX, double domainSizeY, double domainSizeZ,
                                                           double cutOffRadius,
                                                           const std::array<double, 3> &domainStartPosition)
        : domainSizeX(domainSizeX), domainSizeY(domainSizeY), domainSizeZ(domainSizeZ), cutOffRadius(cutOffRadius),
          domainStartPosition(domainStartPosition) {
    createCells();
}

void ParticleContainerLinkedCells::createCells() {
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

    //The curreontPosition has to be adapted according to the cell dimensions
    currentPosition = {domainStartPosition[0] - Cell::sizeX,
                       domainStartPosition[1] - Cell::sizeY,
                       domainStartPosition[2] - Cell::sizeZ};

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
    setNeighbourCells();
}

void ParticleContainerLinkedCells::buildStandardSlice() {
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
    currentPosition[2] += Cell::sizeZ;
}

void ParticleContainerLinkedCells::buildStandardLine() {
    double oldPositionX = currentPosition[0];
    addSingleHaloCell();
    addSingleBoundaryCell();
    buildOneRowInXdirection(numberCellsX - 4, Cell::INNER_CELL);
    addSingleBoundaryCell();
    addSingleHaloCell();
    currentPosition[0] = oldPositionX;
    currentPosition[1] += Cell::sizeY;
}

void ParticleContainerLinkedCells::addSingleHaloCell() {
    cells[currentIndexInCells] = Cell(currentPosition, Cell::HALO_CELL);
    haloCells[currentIndexHaloCells] = &cells[currentIndexInCells];
    currentIndexInCells++;
    currentIndexHaloCells++;
    currentPosition[0] += Cell::sizeX;
}

void ParticleContainerLinkedCells::addSingleBoundaryCell() {
    cells[currentIndexInCells] = Cell(currentPosition, Cell::BOUNDARY_CELL);
    boundaryCells[currentIndexBoundaryCells] = &cells[currentIndexInCells];
    currentIndexInCells++;
    currentIndexBoundaryCells++;
    currentPosition[0] += Cell::sizeX;
}

//Important: This simulation changes the xPostion of the currentPosition
void ParticleContainerLinkedCells::buildOneRowInXdirection(int numberStonesInXdirection, int cellType) {
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

void ParticleContainerLinkedCells::setDimensionsOfCellPointerVectors() {
    boundaryCells.resize(
            (numberCellsX - 2) * (numberCellsZ - 2) * 2 + (numberCellsX - 2) * ((numberCellsY - 2) - 2) * 2 +
            (numberCellsZ - 4) * (numberCellsY - 4) * 2);
    haloCells.resize(numberCellsX * numberCellsZ * 2 + numberCellsX * (numberCellsY - 2) * 2 +
                     (numberCellsZ - 2) * (numberCellsY - 2) * 2);;
    innerCells.resize((numberCellsX - 4) * (numberCellsY - 4) * (numberCellsZ - 4));;
}

void ParticleContainerLinkedCells::buildHaloSlice() {
    double oldPositionX = currentPosition[0];
    double oldPositionY = currentPosition[1];
    //building the first slice which consists only out of halo cells
    for (int i = 0; i < numberCellsY; i++) {
        buildFullLineHaloCells();
    }
    currentPosition[0] = oldPositionX;
    currentPosition[1] = oldPositionY;
    currentPosition[2] += Cell::sizeZ;

}

void ParticleContainerLinkedCells::buildHaloAndBoundarySlice() {
    double oldPositionY = currentPosition[1];
    //building the first line containing only halo cells
    buildFullLineHaloCells();
    for (int i = 0; i < numberCellsY - 2; ++i) {
        buildLineOneHaloMultipleBoundariesOneHalo();
    }
    buildFullLineHaloCells();
    //building the second line containing halo and boundary cells
    currentPosition[1] = oldPositionY;
    currentPosition[2] += Cell::sizeZ;
}

void ParticleContainerLinkedCells::buildFullLineHaloCells() {
    double oldPositionX = currentPosition[0];
    buildOneRowInXdirection(numberCellsX, Cell::HALO_CELL);
    currentPosition[0] = oldPositionX;
    currentPosition[1] += Cell::sizeY;
}

void ParticleContainerLinkedCells::buildLineOneHaloMultipleBoundariesOneHalo() {
    double oldPositionX = currentPosition[0];
    addSingleHaloCell();
    buildOneRowInXdirection(numberCellsX - 2, Cell::BOUNDARY_CELL);
    addSingleHaloCell();
    currentPosition[0] = oldPositionX;
    currentPosition[1] += Cell::sizeY;
}

void ParticleContainerLinkedCells::walkOverParticles(ParticleVisitor &visitor) {
    for (Cell &c : cells) {
        for (Particle &p : c.getParticles()) {
            visitor.visitParticle(p);
        }
    }
}

void ParticleContainerLinkedCells::walkOverParticlePairs(ParticlePairVisitor &visitor) {
    for (Cell &c : cells) {
        for (Particle &p1 : c.getParticles()) {
            for (Cell *c2 : c.getNeighbourCells()) {
                for (Particle &p2 : c2->getParticles()) {
                    if (ArrayUtils::L2Norm(p1.getX() - p2.getX()) <= cutOffRadius){
                        visitor.visitParticlePair(p1, p2);
                    }
                }
            }
        }
    }
}

void ParticleContainerLinkedCells::setNeighbourCells() {
    for (int i = 0; i < cells.size(); ++i) {
        auto neighbourIndices = getNeighbourIndices(i);
        for (auto index : neighbourIndices) {
            if (index != -1){
                cells[i].addCellToNeighbours(&cells[index]);
            }
        }
    }
}

std::array<int, 26> ParticleContainerLinkedCells::getNeighbourIndices(int index) {
    std::array<int, 26> resultArray{};
    //not all cells have 26 neighbours and -1 stands for no neighbour
    for (int i = 0; i < 26; ++i) {
        resultArray[i] = -1;
    }
    int currentXIndex;
    int currentYIndex;
    int currentNeighbourIndex;
    int counter = 0;
    for (int i = -1; i < 2; ++i) {
        //move by i in x direction
        currentXIndex = movePositionsInX(index, i);
        if (currentXIndex < 0){
            continue;
        }
        for (int j = -1; j < 2; ++j) {
            //move by j in y direction
            currentYIndex = movePositionsInY(currentXIndex, j);
            if (currentYIndex < 0){
                continue;
            }
            for (int k = -1; k < 2; ++k) {
                if (i == 0 && j == 0 && k == 0){
                    continue;
                }
                //move by k in z direction
                currentNeighbourIndex = movePositionsInZ(currentYIndex, k);
                //only add neighbour if it has a larger index to avoid duplicate force calculation
                if (currentNeighbourIndex < index || currentNeighbourIndex < 0 || currentNeighbourIndex > cells.size()){
                    currentNeighbourIndex = -1;
                }
                resultArray[counter] = currentNeighbourIndex;
                counter++;
            }
        }
    }
    return resultArray;
}

int ParticleContainerLinkedCells::movePositionsInX(int index, int numberPositionsInX) {
    return index + numberPositionsInX;
}

int ParticleContainerLinkedCells::movePositionsInY(int index, int numberPositionsInY) {
    return index + numberCellsX * numberPositionsInY;
}

int ParticleContainerLinkedCells::movePositionsInZ(int index, int numberPositionsInZ) {
    return index + numberCellsX * numberCellsY * numberPositionsInZ;
}

int ParticleContainerLinkedCells::getCellIndexForParticle(const Particle &p){
    int indexX = int(p.getX()[0] / Cell::sizeX)+1;
    int indexY = int(p.getX()[1] / Cell::sizeY)+1;
    int indexZ = int(p.getX()[2] / Cell::sizeZ)+1;
    int indexCombined = indexX + indexY * numberCellsX + indexZ * numberCellsX * numberCellsY;
    return indexCombined;
}

void ParticleContainerLinkedCells::addParticleToContainer(Particle &p) {
    //calculate index of cell this particle belongs to
    int index = getCellIndexForParticle(p);
    cells[index].getParticles().push_back(p);
}

void ParticleContainerLinkedCells::cellsToXYZ() {
    std::vector<Particle> linkedCellParticles;
    //std::vector<Particle> linkedCellParticles = std::vector<Particle>(cells.size());
    for (int i = 0; i < cells.size(); ++i) {
        linkedCellParticles.emplace_back(cells[i].getPosition(), std::array<double, 3>{1,1,1}, 100, cells[i].getCellType(),i);
    }
    //At this index we get an error in the VTKWriter
    std::cout << linkedCellParticles[21].getX()[1] << std::endl;
    VTKWriter writer = VTKWriter();
    writer.writeParticlesToFile("LinkedCells", 1, linkedCellParticles);
    std::cout << "Fertig" << std::endl;
}

const std::vector<Cell *> &ParticleContainerLinkedCells::getBoundaryCells() const {
    return boundaryCells;
}

const std::vector<Cell *> &ParticleContainerLinkedCells::getHaloCells() const {
    return haloCells;
}

const std::vector<Cell *> &ParticleContainerLinkedCells::getInnerCells() const {
    return innerCells;
}

const std::vector<Cell>& ParticleContainerLinkedCells::getCells() const {
    return cells;
}

std::vector<Particle> & ParticleContainerLinkedCells::getParticles() {
    ParticleCollector pc;
    walkOverParticles(pc);
    return pc.getParticles();
}

ParticleContainerLinkedCells::ParticleContainerLinkedCells() {}

void ParticleContainerLinkedCells::updateParticlePositions(ParticleVisitor &visitor) {
    for (Cell &c : cells) {
        std::vector<Particle>& particlesInCell = c.getParticles();
        for (int i = 0; i < particlesInCell.size(); ++i) {
            //apply actual implementation of position calculation
            visitor.visitParticle(particlesInCell[i]);
            //calculate new cell the particle belongs to
            int indexNewCell = getCellIndexForParticle(particlesInCell[i]);
            if (indexNewCell >= cells.size() || indexNewCell < 0){
                //TODO das sollte die boundary condition verhindern, hier wird jetzt einfach gelöscht
                particlesInCell.erase(particlesInCell.begin()+i);
                i--;
                continue;
            }
            if (!(cells[indexNewCell] == c)){
                //Particle p has to be moved from c to newCell
                //TODO hier wird kopiert
                cells[indexNewCell].getParticles().push_back(particlesInCell[i]);
                particlesInCell.erase(particlesInCell.begin()+i);
                i--;
            }
        }
    }
}