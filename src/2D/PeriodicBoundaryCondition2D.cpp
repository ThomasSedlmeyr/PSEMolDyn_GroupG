//
// Created by thomas on 16.12.21.
//

#include "PeriodicBoundaryCondition2D.h"
#include "ParticleContainerLinkedCells2D.h"

namespace twoD {

    bool PeriodicBoundaryCondition2D::isDebug = false;
    bool PeriodicBoundaryCondition2D::isBottomPeriodic = false;
    bool PeriodicBoundaryCondition2D::isRightPeriodic = false;

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
                        if (!particle.isGhostParticle) {
                            reflectPositionToGhostLeftX(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
            case LEFT:
                for (auto &haloCell: specificHaloCells) {
                    for (auto &particle: haloCell->getParticles()) {
                        if (!particle.isGhostParticle) {
                            reflectPositionToGhostRightX(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
            case TOP:
                for (auto &haloCell: specificHaloCells) {
                    for (auto &particle: haloCell->getParticles()) {
                        if (!particle.isGhostParticle) {
                            reflectPositionToGhostBottomY(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
            case BOTTOM:
                for (auto &haloCell: specificHaloCells) {
                    for (auto &particle: haloCell->getParticles()) {
                        if (!particle.isGhostParticle) {
                            reflectPositionToGhostTopY(particle.getXRef());
                            ParticleContainerLinkedCells2D::addParticle(particle);
                        }
                    }
                }
                break;
        }
        deleteAllParticlesInHaloCells();
        insertGhostParticles();
    }

    void PeriodicBoundaryCondition2D::insertGhostParticles() {
        switch (side) {
            case RIGHT:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                    //Create particles in the corners if we have on all sides PeriodicBoundaryConditions
                    //Right_Bottom_Corner
                    if(isBottomPeriodic && isRightPeriodic && cell->getRelativePositionInDomain()[1] == 1){
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostLeftX(position);
                            reflectPositionToGhostTopY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(),
                                                                             particle.getType());
                        }
                    }
                    //Right_Top_Corner
                    if(isBottomPeriodic && isRightPeriodic && cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells2D::numberCellsY - 2){
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostLeftX(position);
                            reflectPositionToGhostBottomY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(),
                                                                             particle.getType());
                        }
                    }
                }
                break;
            case LEFT:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                    //Create particles in the corners if we have on all sides PeriodicBoundaryConditions
                    //Left_Bottom_Corner
                    if (isBottomPeriodic && isRightPeriodic && cell->getRelativePositionInDomain()[1] == 1) {
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostRightX(position);
                            reflectPositionToGhostTopY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(), particle.getType());
                        }

                    }
                    //Left_Top_Corner
                    if (isBottomPeriodic && isRightPeriodic && cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells2D::numberCellsY - 2) {
                        for (auto &particle: cell->getParticles()) {
                            std::array<double, 3> position = particle.getX();
                            reflectPositionToGhostRightX(position);
                            reflectPositionToGhostBottomY(position);
                            ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(), particle.getType());
                        }
                    }
                }
                break;
            case TOP:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostBottomY(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                break;
            case BOTTOM:
                for (auto &cell: specificBoundaryCells) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostTopY(position);
                        ParticleContainerLinkedCells2D::addGhostParticle(position, particle.getM(), particle.getType());
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
        //std::array<std::array<int, 3>, 9> positionsOfNewNeighbours{};
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