//
// Created by thomas on 30.11.21.
//

#include "BoundaryCondition.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include <utility>



void BoundaryCondition::setSpecificCells() {
    switch (side) {
        case FRONT:
            setSpecificCells(std::array<int, 3>{0,0,1}, ParticleContainerLinkedCells::numberCellsZ-1, ParticleContainerLinkedCells::haloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0,0,1}, ParticleContainerLinkedCells::numberCellsZ-2, ParticleContainerLinkedCells::boundaryCells, specificBoundaryCells);
            break;
        case RIGHT:
            setSpecificCells(std::array<int, 3>{1,0,0}, ParticleContainerLinkedCells::numberCellsX-1, ParticleContainerLinkedCells::haloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{1,0,0}, ParticleContainerLinkedCells::numberCellsX-2, ParticleContainerLinkedCells::boundaryCells, specificBoundaryCells);
            break;
        case BACK:
            setSpecificCells(std::array<int, 3>{0,0,1}, 0, ParticleContainerLinkedCells::haloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0,0,1}, 1, ParticleContainerLinkedCells::boundaryCells, specificBoundaryCells);
            break;
        case LEFT:
            setSpecificCells(std::array<int, 3>{1,0,0}, 0, ParticleContainerLinkedCells::haloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{1,0,0}, 1, ParticleContainerLinkedCells::boundaryCells, specificBoundaryCells);
            break;
        case TOP:
            setSpecificCells(std::array<int, 3>{0,1,0}, ParticleContainerLinkedCells::numberCellsY-1, ParticleContainerLinkedCells::haloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0,1,0}, ParticleContainerLinkedCells::numberCellsY-2, ParticleContainerLinkedCells::boundaryCells, specificBoundaryCells);
            break;
        case BOTTOM:
            setSpecificCells(std::array<int, 3>{0,1,0}, 0, ParticleContainerLinkedCells::haloCells, specificHaloCells);
            setSpecificCells(std::array<int, 3>{0, 1, 0}, 1, ParticleContainerLinkedCells::boundaryCells,
                             specificBoundaryCells);
            break;
    }
}

void BoundaryCondition::setSpecificCells(std::array<int, 3> relativePositionMask, int relativePositionValue,
                                         std::vector<Cell *>& cells, std::vector<Cell*>& matchingCells) {
    std::array<int, 3> vector{};
    for (auto cell : cells) {
        vector[0] = cell->getRelativePositionInDomain()[0]*relativePositionMask[0];
        vector[1] = cell->getRelativePositionInDomain()[1]*relativePositionMask[1];
        vector[2] = cell->getRelativePositionInDomain()[2]*relativePositionMask[2];
        double sum = vector[0] + vector[1] + vector[2];

        if(relativePositionValue == sum){
            matchingCells.push_back(cell);
        }
    }
}

void BoundaryCondition::deleteAllParticlesInHaloCells() {
    for (auto &specificHaloCell: specificHaloCells) {
        specificHaloCell->getParticles().clear();
    }
}

void BoundaryCondition::deleteGhostParticlesInBoundaryCells() {
    for (auto &cell: specificBoundaryCells) {
        int numberOfGhostParticles = 0;
        //This for loop can be eliminated if we store the number of inserted ghost particles for each cell
        for (auto &particle: cell->getParticles()) {
            if (particle.isGhostParticle) {
                numberOfGhostParticles++;
            }
        }
        if (numberOfGhostParticles > 0) {
            std::cout << "Had to delete ghost particle in boundary cell";
            std::vector<Particle> particles = std::vector<Particle>(
                    cell->getParticles().size() - numberOfGhostParticles);
            for (int i = 0; i < static_cast<int>(cell->getParticles().size()); i++) {
                if (!particles[i].isGhostParticle) {
                    particles[i] = cell->getParticles()[i];
                }
            }
            cell->getParticles() = particles;
        }
    }
}

BoundaryCondition::BoundaryCondition(int conditionType, int side) : conditionType(conditionType), side(side) {
    setSpecificCells();
}

BoundaryCondition::BoundaryCondition() {}

const std::vector<Cell *> &BoundaryCondition::getSpecificBoundaryCells() const {
    return specificBoundaryCells;
}

const std::vector<Cell *> &BoundaryCondition::getSpecificHaloCells() const {
    return specificHaloCells;
}
