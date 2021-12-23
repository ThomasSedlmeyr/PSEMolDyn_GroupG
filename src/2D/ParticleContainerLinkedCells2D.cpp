//
// Created by thomas on 24.11.21.
//

#include <OutputWriter/XYZWriter.h>
#include <OutputWriter/VTKWriter.h>
#include <iostream>
#include <Visitors/ParticleCollector.h>
#include <Visitors/LJForceVisitor.h>
#include "ParticleContainerLinkedCells2D.h"
#include "utils/ArrayUtils.h"
#include "utils/FastMath.h"
namespace twoD{
    std::vector<Cell> ParticleContainerLinkedCells2D::cells;
    int ParticleContainerLinkedCells2D::numberCellsX;
    int ParticleContainerLinkedCells2D::numberCellsY;
    double ParticleContainerLinkedCells2D::domainSizeX;
    double ParticleContainerLinkedCells2D::domainSizeY;
    std::vector<Cell *> ParticleContainerLinkedCells2D::boundaryCells;
    std::vector<Cell *> ParticleContainerLinkedCells2D::haloCells;
    std::vector<Cell *> ParticleContainerLinkedCells2D::innerCells;
    ParticleCollector pc;

    ParticleContainerLinkedCells2D::ParticleContainerLinkedCells2D() = default;

    ParticleContainerLinkedCells2D::ParticleContainerLinkedCells2D(double domainSizeX, double domainSizeY,
                                                                   double cutOffRadius,
                                                                   const std::array<int, 4> &boundaryConditionTypes)
            : cutOffRadius(cutOffRadius) {
        ParticleContainerLinkedCells2D::domainSizeX = domainSizeX;
        ParticleContainerLinkedCells2D::domainSizeY = domainSizeY;
        createCells();
        std::array<double, 3> domainSize = {domainSizeX, domainSizeY, 0};
        boundaryContainer = std::make_unique<BoundaryConditionContainer2D>(boundaryConditionTypes,
                                                                           numberCellsX,
                                                                           numberCellsY, domainSize);
    }

    void ParticleContainerLinkedCells2D::createCells() {
        numberCellsX = int(domainSizeX / cutOffRadius);
        numberCellsY = int(domainSizeY / cutOffRadius);

        Cell::sizeX = double(domainSizeX) / numberCellsX;
        Cell::sizeY = double(domainSizeY) / numberCellsY;
        //to ensure that Cell::particleLiesInCell() works correctly
        Cell::sizeZ = 1000;

        //Two is added because of the HaloCells
        numberCellsX += 2;
        numberCellsY += 2;

        cells.resize(numberCellsX * numberCellsY);

        //The curreontPosition has to be adapted according to the cell dimensions
        currentPosition = {-Cell::sizeX,
                           -Cell::sizeY,
                           0};

        setDimensionsOfCellPointerVectors();
        buildStandardSlice();
        setRelativeDomainPositionsInCells();
        setNeighbourCells();
    }

    void ParticleContainerLinkedCells2D::buildStandardSlice() {
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
    }

    void ParticleContainerLinkedCells2D::buildStandardLine() {
        double oldPositionX = currentPosition[0];
        addSingleHaloCell();
        addSingleBoundaryCell();
        buildOneRowInXdirection(numberCellsX - 4, Cell::INNER_CELL);
        addSingleBoundaryCell();
        addSingleHaloCell();
        currentPosition[0] = oldPositionX;
        currentPosition[1] += Cell::sizeY;
    }

    void ParticleContainerLinkedCells2D::addSingleHaloCell() {
        cells[currentIndexInCells] = Cell(currentPosition, Cell::HALO_CELL);
        haloCells[currentIndexHaloCells] = &cells[currentIndexInCells];
        currentIndexInCells++;
        currentIndexHaloCells++;
        currentPosition[0] += Cell::sizeX;
    }

    void ParticleContainerLinkedCells2D::addSingleBoundaryCell() {
        cells[currentIndexInCells] = Cell(currentPosition, Cell::BOUNDARY_CELL);
        boundaryCells[currentIndexBoundaryCells] = &cells[currentIndexInCells];
        currentIndexInCells++;
        currentIndexBoundaryCells++;
        currentPosition[0] += Cell::sizeX;
    }

//Important: This simulation changes the xPostion of the currentPosition
    void ParticleContainerLinkedCells2D::buildOneRowInXdirection(int numberStonesInXdirection, int cellType) {
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

    void ParticleContainerLinkedCells2D::setDimensionsOfCellPointerVectors() {
        boundaryCells.resize(2*(numberCellsX-2) + 2 * (numberCellsY - 4));
        haloCells.resize(2*numberCellsX + 2 * (numberCellsY-2));;
        innerCells.resize((numberCellsX - 4) * (numberCellsY - 4));
    }


    void ParticleContainerLinkedCells2D::buildFullLineHaloCells() {
        double oldPositionX = currentPosition[0];
        buildOneRowInXdirection(numberCellsX, Cell::HALO_CELL);
        currentPosition[0] = oldPositionX;
        currentPosition[1] += Cell::sizeY;
    }

    void ParticleContainerLinkedCells2D::buildLineOneHaloMultipleBoundariesOneHalo() {
        double oldPositionX = currentPosition[0];
        addSingleHaloCell();
        buildOneRowInXdirection(numberCellsX - 2, Cell::BOUNDARY_CELL);
        addSingleHaloCell();
        currentPosition[0] = oldPositionX;
        currentPosition[1] += Cell::sizeY;
    }

    void ParticleContainerLinkedCells2D::setRelativeDomainPositionsInCells() {
        int index = 0;
        for (int y = 0; y < numberCellsY; y++) {
            for (int x = 0; x < numberCellsX; x++) {
                cells[index].setRelativePositionInDomain(std::array<int, 3>{x, y, 0});
                index++;
            }
        }
    }

    void ParticleContainerLinkedCells2D::walkOverParticles(ParticleVisitor &visitor) {
        for (Cell &c: cells) {
            for (Particle &p: c.getParticles()) {
                visitor.visitParticle(p);
            }
        }
    }

    bool ParticleContainerLinkedCells2D::shouldCalculateForce(const std::array<double, 3> &pos1, const std::array<double, 3> &pos2, double cutOffRadius) {
        std::array<double, 3> diff{};
        double squaredNorm = 0;
        double singleDiff;

        for (int i = 0; i < 3; ++i) {
            singleDiff = pos1[i] - pos2[i];
            diff[i] = singleDiff;
            squaredNorm += singleDiff * singleDiff;
        }
        return squaredNorm < cutOffRadius * cutOffRadius;
    }

    void ParticleContainerLinkedCells2D::walkOverParticlePairs(ParticlePairVisitor &visitor) {
        boundaryContainer->calculateBoundaryConditions();
        for (Cell &c: cells) {
            auto &particles = c.getParticles();
            for (auto it = particles.begin(); it != particles.end(); it++) {
                //apply Gravitation
                if (useGrav){
                    std::array<double, 3> &f = it->getFRef();
                    f[1] += it->getM()*g_grav;
                }
                //calculate force between particles inside of cell
                for (auto it2 = it + 1; it2 != particles.end(); it2++) {
                    if (shouldCalculateForce(it->getX(), it2->getX(), cutOffRadius)) {
                        visitor.visitParticlePair(*it, *it2);
                    }
                }
            }
            for (Cell *c2: c.getNeighbourCells()) {
                auto &particles2 = c2->getParticles();
                for (auto & particle : particles) {
                    for (Particle &p2: particles2) {
                        if (shouldCalculateForce(particle.getX(), p2.getX(), cutOffRadius)) {
                            visitor.visitParticlePair(particle, p2);
                        }
                    }
                }
            }
        }
        boundaryContainer->doWorkAfterCalculationStep();
    }

    void ParticleContainerLinkedCells2D::setNeighbourCells() {
        for (std::size_t i = 0; i < cells.size(); ++i) {
            auto neighbourIndices = getNeighbourIndices(static_cast<int> (i));
            for (auto index: neighbourIndices) {
                if (index != -1) {
                    cells[i].addCellToNeighbours(&cells[index]);
                }
            }
        }
    }

    std::array<int, 8> ParticleContainerLinkedCells2D::getNeighbourIndices(int index) {
        std::array<int, 8> resultArray{};
        //not all cells have 8 neighbours and -1 stands for no neighbour
        for (int i = 0; i < 8; ++i) {
            resultArray[i] = -1;
        }
        int currentXIndex;
        int currentNeighbourIndex;
        int counter = 0;
        for (int i = -1; i < 2; ++i) {
            //move by i in x direction
            currentXIndex = movePositionsInX(index, i);
            if (currentXIndex < 0) {
                continue;
            }
            for (int j = -1; j < 2; ++j) {
                if (i == 0 && j == 0) {
                    continue;
                }
                currentNeighbourIndex = movePositionsInY(currentXIndex, j);
                if (currentNeighbourIndex > index && currentNeighbourIndex >= 0 &&
                    currentNeighbourIndex < static_cast<int>(cells.size())) {
                    resultArray[counter] = currentNeighbourIndex;
                    counter++;
                }
            }
        }
        return resultArray;
    }

    int ParticleContainerLinkedCells2D::movePositionsInX(int index, int numberPositionsInX) {
        if (numberPositionsInX == 0) {
            return index;
        }
        auto resultIndex = index + numberPositionsInX;
        if (resultIndex < 0) {
            return -1;
        }
        if (resultIndex >= cells.size()){
            return -1;
        }
        if (resultIndex > index) {
            //moved to right, so x position of new cell has to be greater
            if (cells[resultIndex].getPosition()[0] > cells[index].getPosition()[0]) {
                return resultIndex;
            }
            return -1;
        }
        //moved to left, so x position of new cell has to be smaller
        if (cells[resultIndex].getPosition()[0] < cells[index].getPosition()[0]) {
            return resultIndex;
        }
        return -1;
    }

    int ParticleContainerLinkedCells2D::movePositionsInY(int index, int numberPositionsInY) {
        if (numberPositionsInY == 0) {
            return index;
        }
        auto resultIndex = index + numberCellsX * numberPositionsInY;
        if (resultIndex < 0) {
            return -1;
        }
        if (resultIndex >= cells.size()){
            return -1;
        }
        if (resultIndex > index) {
            //moved upward, so y position of new cell has to be greater
            if (cells[resultIndex].getPosition()[1] > cells[index].getPosition()[1]) {
                return resultIndex;
            }
            return -1;
        }
        //moved down, so y position of new cell has to be smaller
        if (cells[resultIndex].getPosition()[1] < cells[index].getPosition()[1]) {
            return resultIndex;
        }
        return -1;
    }

    int ParticleContainerLinkedCells2D::getCellIndexForParticle(const Particle &p) {
        //the following calculation assumes that the first cell is at (0,0,0)
        //to use it even when the position is not (0,0,0), the position has to be offset accordingly
        auto particlePositionWithOffset = p.getX() - cells[0].getPosition();
        int indexX = int(particlePositionWithOffset[0] / Cell::sizeX);
        int indexY = int(particlePositionWithOffset[1] / Cell::sizeY);
        int indexCombined = indexX + indexY * numberCellsX;
        return indexCombined;
    }

    void ParticleContainerLinkedCells2D::addParticleToContainer(Particle &p) {
        //calculate index of cell this particle belongs to
        int index = getCellIndexForParticle(p);
        cells[index].getParticles().push_back(p);
    }

    void ParticleContainerLinkedCells2D::cellsToVTK() {
        std::vector<Particle> linkedCellParticles;
        //std::vector<Particle> linkedCellParticles = std::vector<Particle>(cells.size());
        linkedCellParticles.reserve(cells.size());

        for (std::size_t i = 0; i < cells.size(); ++i) {
            linkedCellParticles.emplace_back(cells[i].getPosition(), std::array<double, 3>{1, 1, 1}, 100,
                                             cells[i].getCellType(), i);
        }
        //std::cout << linkedCellParticles[21].getX()[1] << std::endl;
        VTKWriter writer = VTKWriter();
        writer.writeParticlesToFile("LinkedCells", 1, linkedCellParticles);
        //std::cout << "Fertig" << std::endl;
    }

    const std::vector<Cell *> &ParticleContainerLinkedCells2D::getBoundaryCells() {
        return boundaryCells;
    }

    const std::vector<Cell *> &ParticleContainerLinkedCells2D::getHaloCells() {
        return haloCells;
    }

    const std::vector<Cell *> &ParticleContainerLinkedCells2D::getInnerCells() {
        return innerCells;
    }

    const std::vector<Cell> &ParticleContainerLinkedCells2D::getCells() {
        return cells;
    }

    std::vector<Particle> &ParticleContainerLinkedCells2D::getParticles() {
        pc.getParticles().clear();
        walkOverParticles(pc);
        return pc.getParticles();
    }

    void ParticleContainerLinkedCells2D::updateParticlePositions(ParticleVisitor &visitor) {
        for (Cell &c: cells) {
            std::vector<Particle> &particlesInCell = c.getParticles();
            for (std::size_t i = 0; i < particlesInCell.size(); ++i) {
                Particle &p = particlesInCell[i];
                //apply actual implementation of position calculation
                visitor.visitParticle(p);
                //calculate new cell the particle belongs to
                int indexNewCell = getCellIndexForParticle(p);
                if (indexNewCell < 0 || indexNewCell > static_cast<int>(cells.size())) {
                    std::cout << "Error, Particle got outside of domain!";
                    particlesInCell.erase(particlesInCell.begin() + i);
                    i--;
                    continue;
                    //exit(1);
                }
                Cell &newCell = cells[indexNewCell];
                if (!(newCell == c)) {
                    if (!newCell.particleLiesInCell(p)) {
                        std::cout << "Error, Particle got outside of domain!";
                        //exit(1);
                        particlesInCell.erase(particlesInCell.begin() + i);
                        i--;
                        continue;
                    }
                    //Particle p has to be moved from c to newCell
                    newCell.getParticles().push_back(particlesInCell[i]);
                    particlesInCell.erase(particlesInCell.begin() + i);
                    i--;
                }
            }
        }
    }

    void ParticleContainerLinkedCells2D::addGhostParticle(const std::array<double, 3> &position, const double m, const int type) {
        Particle p = Particle(position, {0, 0, 0}, m, type);
        p.isGhostParticle = true;
        auto index = getCellIndexForParticle(p);
        cells[index].getParticles().push_back(p);
    }

    void ParticleContainerLinkedCells2D::addParticle(Particle &particle) {
        auto index = getCellIndexForParticle(particle);
        cells[index].getParticles().push_back(particle);
    }
}