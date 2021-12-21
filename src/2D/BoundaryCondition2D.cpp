//
// Created by thomas on 30.11.21.
//

#include "BoundaryCondition2D.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

namespace twoD {
    void BoundaryCondition2D::setSpecificCells() {
        switch (side) {
            case RIGHT:
                setSpecificCells(std::array<int, 2>{1, 0}, ParticleContainerLinkedCells::numberCellsX - 1,
                                 ParticleContainerLinkedCells::haloCells, specificHaloCells);
                setSpecificCells(std::array<int, 2>{1, 0}, ParticleContainerLinkedCells::numberCellsX - 2,
                                 ParticleContainerLinkedCells::boundaryCells, specificBoundaryCells);
                break;
            case LEFT:
                setSpecificCells(std::array<int, 2>{1, 0}, 0, ParticleContainerLinkedCells::haloCells,
                                 specificHaloCells);
                setSpecificCells(std::array<int, 2>{1, 0}, 1, ParticleContainerLinkedCells::boundaryCells,
                                 specificBoundaryCells);
                break;
            case TOP:
                setSpecificCells(std::array<int, 2>{0, 1}, ParticleContainerLinkedCells::numberCellsY - 1,
                                 ParticleContainerLinkedCells::haloCells, specificHaloCells);
                setSpecificCells(std::array<int, 2>{0, 1}, ParticleContainerLinkedCells::numberCellsY - 2,
                                 ParticleContainerLinkedCells::boundaryCells, specificBoundaryCells);
                break;
            case BOTTOM:
                setSpecificCells(std::array<int, 2>{0, 1}, 0, ParticleContainerLinkedCells::haloCells,
                                 specificHaloCells);
                setSpecificCells(std::array<int, 2>{0, 1}, 1, ParticleContainerLinkedCells::boundaryCells,
                                 specificBoundaryCells);
                break;
        }
    }

    void BoundaryCondition2D::setSpecificCells(std::array<int, 2> relativePositionMask, int relativePositionValue,
                                               std::vector<Cell *> &cells, std::vector<Cell *> &matchingCells) {
        std::array<int, 2> vector{};
        for (auto cell: cells) {
            vector[0] = cell->getRelativePositionInDomain()[0] * relativePositionMask[0];
            vector[1] = cell->getRelativePositionInDomain()[1] * relativePositionMask[1];
            double sum = vector[0] + vector[1];

            if (relativePositionValue == sum) {
                matchingCells.push_back(cell);
            }
        }
    }

    void BoundaryCondition2D::deleteAllParticlesInHaloCells() {
        for (auto &specificHaloCell: specificHaloCells) {
            specificHaloCell->getParticles().clear();
        }
    }

    BoundaryCondition2D::BoundaryCondition2D(int conditionType, int side) : conditionType(conditionType), side(side) {
        setSpecificCells();
    }

    BoundaryCondition2D::BoundaryCondition2D() {}

    const std::vector<Cell *> &BoundaryCondition2D::getSpecificBoundaryCells() const {
        return specificBoundaryCells;
    }

    const std::vector<Cell *> &BoundaryCondition2D::getSpecificHaloCells() const {
        return specificHaloCells;
    }
}