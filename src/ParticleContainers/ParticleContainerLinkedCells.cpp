//
// Created by thomas on 24.11.21.
//

#include <OutputWriter/XYZWriter.h>
#include <OutputWriter/VTKWriter.h>
#include <iostream>
#include <Visitors/ParticleCollector.h>
#include "ParticleContainerLinkedCells.h"
#include "utils/ArrayUtils.h"

std::vector<Cell> ParticleContainerLinkedCells::cells;
int ParticleContainerLinkedCells::numberCellsX;
int ParticleContainerLinkedCells::numberCellsY;
int ParticleContainerLinkedCells::numberCellsZ;
std::vector<Cell*> ParticleContainerLinkedCells::boundaryCells;
std::vector<Cell*> ParticleContainerLinkedCells::haloCells;
std::vector<Cell*> ParticleContainerLinkedCells::innerCells;
ParticleCollector pc;

ParticleContainerLinkedCells::ParticleContainerLinkedCells() = default;

ParticleContainerLinkedCells::ParticleContainerLinkedCells(double domainSizeX, double domainSizeY, double domainSizeZ,
                                                           double cutOffRadius,
                                                           const std::array<int, 6> &boundaryConditionTypes)
        : domainSizeX(domainSizeX), domainSizeY(domainSizeY), domainSizeZ(domainSizeZ), cutOffRadius(cutOffRadius) {

    createCells();
    std::array<int, 6> ones = {1, 1, 1, 1, 1, 1};
    std::array<int, 6> twos = {2, 2, 2, 2, 2, 2};
    std::array<double, 3> domainSize = {domainSizeX, domainSizeY, domainSizeZ};
    boundaryContainer = std::make_unique<BoundaryConditionContainer>(boundaryConditionTypes, boundaryCells, haloCells,
                                                                     numberCellsX,
                                                                     numberCellsY, numberCellsZ, domainSize);
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
    currentPosition = {-Cell::sizeX,
                       -Cell::sizeY,
                       -Cell::sizeZ};

    setDimensionsOfCellPointerVectors();

    buildHaloSlice();
    buildHaloAndBoundarySlice();
    for (int z = 0; z < numberCellsZ - 4; ++z) {
        buildStandardSlice();
    }
    buildHaloAndBoundarySlice();
    buildHaloSlice();
    setRelativeDomainPositionsInCells();
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
    innerCells.resize((numberCellsX - 4) * (numberCellsY - 4) * (numberCellsZ - 4));
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

void ParticleContainerLinkedCells::setRelativeDomainPositionsInCells(){
    int index = 0;
    for (int z = 0; z < numberCellsZ; ++z) {
        for(int y = 0; y < numberCellsY; y++){
            for(int x = 0; x < numberCellsX; x++){
                cells[index].setRelativePositionInDomain(std::array<int, 3>{x, y, z});
                index++;
            }
        }
    }
}

void ParticleContainerLinkedCells::walkOverParticles(ParticleVisitor &visitor) {
    for (Cell &c : cells) {
        for (Particle &p : c.getParticles()) {
            visitor.visitParticle(p);
        }
    }
}

void ParticleContainerLinkedCells::walkOverParticlePairs(ParticlePairVisitor &visitor) {
    boundaryContainer->calculateBoundaryConditions();
    for (Cell &c : cells) {
        auto &particles = c.getParticles();
        for (auto it = particles.begin(); it != particles.end(); it++){
            //calculate force between particles inside of cell
            for (auto it2 = it + 1; it2 != particles.end(); it2++) {
                visitor.visitParticlePair(*it, *it2);
            }
            //calculate force between particles in different cells
            for (Cell *c2 : c.getNeighbourCells()) {
                for (Particle &p2 : c2->getParticles()) {
                    auto distance = ArrayUtils::L2Norm((*it).getX() - p2.getX());
                    //TODO brauchen wir diese abfrage überhaupt?
                    if (distance <= cutOffRadius){
                        visitor.visitParticlePair(*it, p2);
                    }
                }
            }
        }
    }
    boundaryContainer->doWorkAfterCalculationStep();
}

void ParticleContainerLinkedCells::setNeighbourCells() {
    for (std::size_t i = 0; i < cells.size(); ++i) {
        auto neighbourIndices = getNeighbourIndices(static_cast<int> (i));
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
                if (currentNeighbourIndex > index && currentNeighbourIndex >= 0 && currentNeighbourIndex < static_cast<int>(cells.size())){
                    resultArray[counter] = currentNeighbourIndex;
                    counter++;
                }
            }
        }
    }
    return resultArray;
}

int ParticleContainerLinkedCells::movePositionsInX(int index, int numberPositionsInX) {
    if (numberPositionsInX == 0){
        return index;
    }
    auto resultIndex = index + numberPositionsInX;
    if (resultIndex < 0){
        return -1;
    }
    if (resultIndex > index){
        //moved to right, so x position of new cell has to be greater
        if (cells[resultIndex].getPosition()[0] > cells[index].getPosition()[0]){
            return resultIndex;
        }
        return -1;
    }
    //moved to left, so x position of new cell has to be smaller
    if (cells[resultIndex].getPosition()[0] < cells[index].getPosition()[0]){
        return resultIndex;
    }
    return -1;
}

int ParticleContainerLinkedCells::movePositionsInY(int index, int numberPositionsInY) {
    if (numberPositionsInY == 0){
        return index;
    }
    auto resultIndex =  index + numberCellsX * numberPositionsInY;
    if (resultIndex < 0){
        return -1;
    }
    if (resultIndex > index){
        //moved upward, so y position of new cell has to be greater
        if (cells[resultIndex].getPosition()[1] > cells[index].getPosition()[1]){
            return resultIndex;
        }
        return -1;
    }
    //moved down, so y position of new cell has to be smaller
    if (cells[resultIndex].getPosition()[1] < cells[index].getPosition()[1]){
        return resultIndex;
    }
    return -1;
}

int ParticleContainerLinkedCells::movePositionsInZ(int index, int numberPositionsInZ) {
    return index + numberCellsX * numberCellsY * numberPositionsInZ;
}

int ParticleContainerLinkedCells::getCellIndexForParticle(const Particle &p){
    //the following calculation assumes that the first cell is at (0,0,0)
    //to use it even when the position is not (0,0,0), the position has to be offset accordingly
    auto particlePositionWithOffset = p.getX() - cells[0].getPosition();
    int indexX = int(particlePositionWithOffset[0] / Cell::sizeX);
    int indexY = int(particlePositionWithOffset[1] / Cell::sizeY);
    int indexZ = int(particlePositionWithOffset[2] / Cell::sizeZ);
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
    linkedCellParticles.reserve(cells.size());
for (std::size_t i = 0; i < cells.size(); ++i) {
        linkedCellParticles.emplace_back(cells[i].getPosition(), std::array<double, 3>{1,1,1}, 100, cells[i].getCellType(),i);
    }
    //At this index we get an error in the VTKWriter
    std::cout << linkedCellParticles[21].getX()[1] << std::endl;
    VTKWriter writer = VTKWriter();
    writer.writeParticlesToFile("LinkedCells", 1, linkedCellParticles);
    std::cout << "Fertig" << std::endl;
}

const std::vector<Cell *> &ParticleContainerLinkedCells::getBoundaryCells() {
    return boundaryCells;
}

const std::vector<Cell *> &ParticleContainerLinkedCells::getHaloCells() {
    return haloCells;
}

const std::vector<Cell *> &ParticleContainerLinkedCells::getInnerCells() {
    return innerCells;
}

const std::vector<Cell>& ParticleContainerLinkedCells::getCells() {
    return cells;
}

std::vector<Particle> & ParticleContainerLinkedCells::getParticles() {
    pc.getParticles().clear();
    walkOverParticles(pc);
    return pc.getParticles();
}

void ParticleContainerLinkedCells::updateParticlePositions(ParticleVisitor &visitor) {
    for (Cell &c : cells) {
        std::vector<Particle>& particlesInCell = c.getParticles();
        for (std::size_t i = 0; i < particlesInCell.size(); ++i) {
            //apply actual implementation of position calculation
            visitor.visitParticle(particlesInCell[i]);
            //calculate new cell the particle belongs to
            int indexNewCell = getCellIndexForParticle(particlesInCell[i]);
            if (indexNewCell < 0 || indexNewCell > static_cast<int>(cells.size())){
                std::cout << "Error, Particle got outside of domain!";
                exit(1);
            }
            Cell &newCell = cells[indexNewCell];
            if (!(newCell == c)){
                if (!newCell.particleLiesInCell(particlesInCell[i])){
                    std::cout << "Error, Particle got outside of domain!";
                    exit(1);
                }
                //Particle p has to be moved from c to newCell
                newCell.getParticles().push_back(particlesInCell[i]);
                particlesInCell.erase(particlesInCell.begin()+i);
                i--;
            }
        }
    }
}

void ParticleContainerLinkedCells::addGhostParticle(const std::array<double, 3> &position, double m) {
    Particle p = Particle(position, {0, 0, 0}, m, -1);
    auto index = getCellIndexForParticle(p);
    cells[index].getParticles().push_back(p);
}

void ParticleContainerLinkedCells::addParticle(Particle &particle) {
    auto index = getCellIndexForParticle(particle);
    cells[index].getParticles().push_back(particle);
}

int ParticleContainerLinkedCells::getNumberOfParticles() {
    int result = 0;
    for (auto &cell: cells) {
        result += cell.getParticles().size();
    }
    return result;
}
