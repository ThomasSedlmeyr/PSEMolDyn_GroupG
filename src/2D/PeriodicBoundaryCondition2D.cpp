//
// Created by thomas on 16.12.21.
//

#include "PeriodicBoundaryCondition2D.h"
#include "ParticleContainerLinkedCells2D.h"

namespace twoD {

    bool PeriodicBoundaryCondition2D::isDebug = false;

    void PeriodicBoundaryCondition2D::doWorkAfterCalculationStep() {
        if (!PeriodicBoundaryCondition2D::isDebug) {
            deleteAllParticlesInHaloCells();
            deleteGhostParticlesInBoundaryCells();
        }
    }

    void PeriodicBoundaryCondition2D::calculateBoundaryCondition() {
        switch (side) {
            case RIGHT:
                for (auto &haloCell: specificHaloCells) {
                    for (auto &particle: haloCell->getParticles()) {
                        if (particle.getType() != Particle::GHOST_TYPE) {
                            reflectPositionToGhostLeftX(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
            case LEFT:
                for (auto &haloCell: specificHaloCells) {
                    for (auto &particle: haloCell->getParticles()) {
                        if (particle.getType() != Particle::GHOST_TYPE) {
                            reflectPositionToGhostRightX(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
            case TOP:
                for (auto &haloCell: specificHaloCells) {
                    for (auto &particle: haloCell->getParticles()) {
                        if (particle.getType() != Particle::GHOST_TYPE) {
                            reflectPositionToGhostBottomY(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
            case BOTTOM:
                for (auto &haloCell: specificHaloCells) {
                    for (auto &particle: haloCell->getParticles()) {
                        if (particle.getType() != Particle::GHOST_TYPE) {
                            reflectPositionToGhostTopY(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
        }
        insertGhostParticles();
    }

    void PeriodicBoundaryCondition2D::insertGhostParticles() {
        switch (side) {
            case RIGHT:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                    }
                    //Right_Bottom_Edge
                    if (cell->getRelativePositionInDomain()[1] == 1) {
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostLeftX(position);
                            reflectPositionToGhostTopY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                        }
                    }
                    //Right_Top_Edge
                    if (cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells2D::numberCellsY - 2) {
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostLeftX(position);
                            reflectPositionToGhostBottomY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                        }
                    }
                }
                break;
            case LEFT:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                    }
                    //Left_Bottom_Edge
                    if (cell->getRelativePositionInDomain()[1] == 1) {
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostRightX(position);
                            reflectPositionToGhostTopY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                        }
                    }
                    //Left_Top_Edge
                    if (cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells2D::numberCellsY - 2) {
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostRightX(position);
                            reflectPositionToGhostBottomY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                        }
                    }
                }
                break;
            case TOP:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostBottomY(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                    }
                }
                break;
            case BOTTOM:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostTopY(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM());
                    }
                }
                break;
        }
    }


    PeriodicBoundaryCondition2D::PeriodicBoundaryCondition2D(int conditionType, int side) : BoundaryCondition2D(conditionType,
                                                                                                          side) {
        addAdditionalNeighbours();
    }

    void PeriodicBoundaryCondition2D::addAdditionalNeighbours() {
        for (auto &specificBoundaryCell: specificBoundaryCells) {
            setNeighbourCell(specificBoundaryCell);
        }
    }

    void PeriodicBoundaryCondition2D::setNeighbourCell(Cell *cell) {
        std::array<std::array<int, 3>, 9> positionsOfNewNeighbours{};
        std::array<int, 3> positionOfPartnerCell = cell->getRelativePositionInDomain();
        switch (side) {
            case RIGHT:

                break;
            case LEFT:
                positionOfPartnerCell[0] = ParticleContainerLinkedCells2D::numberCellsX - 2;
                //ParticleContainerLinkedCells2D::add9CellsAtRelativePositionsToNeighboursOfCell( ,positionOfPartnerCell);
                break;
            case TOP:

                break;
            case BOTTOM:

                break;
        }
    }

    inline void PeriodicBoundaryCondition2D::reflectPositionToGhostRightX(std::array<double, 3> &position) {
        position[0] += ParticleContainerLinkedCells2D::domainSizeX;
    }

    inline void PeriodicBoundaryCondition2D::reflectPositionToGhostLeftX(std::array<double, 3> &position) {
        position[0] -= ParticleContainerLinkedCells2D::domainSizeX;
    }

    inline void PeriodicBoundaryCondition2D::reflectPositionToGhostTopY(std::array<double, 3> &position) {
        position[1] += ParticleContainerLinkedCells2D::domainSizeY;
    }

    inline void PeriodicBoundaryCondition2D::reflectPositionToGhostBottomY(std::array<double, 3> &position) {
        position[1] -= ParticleContainerLinkedCells2D::domainSizeY;
    }
}