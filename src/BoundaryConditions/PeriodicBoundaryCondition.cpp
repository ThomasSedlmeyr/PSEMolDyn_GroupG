//
// Created by thomas on 16.12.21.
//

#include "PeriodicBoundaryCondition.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

bool PeriodicBoundaryCondition::isDebug = false;
bool PeriodicBoundaryCondition::isRightPeriodic = false;
bool PeriodicBoundaryCondition::isBottomPeriodic = false;
bool PeriodicBoundaryCondition::isFrontPeriodic = false;

PeriodicBoundaryCondition::PeriodicBoundaryCondition(int conditionType, int side) : BoundaryCondition(conditionType, side) {}

void PeriodicBoundaryCondition::doWorkAfterCalculationStep() {
    if (!PeriodicBoundaryCondition::isDebug) {
        deleteAllParticlesInHaloCells();
        deleteGhostParticlesInBoundaryCells();
    }
}

void PeriodicBoundaryCondition::calculateBoundaryCondition() {
    switch (side) {
        case FRONT:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    if (!particle.isGhostParticle) {
                        reflectPositionToGhostBackZ(particle.getXRef());
                        ParticleContainerLinkedCells::addParticle(particle);
                    }
                }
            }
            break;
        case BACK:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    if (!particle.isGhostParticle) {
                        reflectPositionToGhostFrontZ(particle.getXRef());
                        ParticleContainerLinkedCells::addParticle(particle);
                    }
                }
            }
            break;
        case RIGHT:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    if (!particle.isGhostParticle) {
                        reflectPositionToGhostLeftX(particle.getXRef());
                        ParticleContainerLinkedCells::addParticle(particle);
                    }
                }
            }
            break;
        case LEFT:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    if (!particle.isGhostParticle) {
                        reflectPositionToGhostRightX(particle.getXRef());
                        ParticleContainerLinkedCells::addParticle(particle);
                    }
                }
            }
            break;
        case TOP:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    if (!particle.isGhostParticle) {
                        reflectPositionToGhostBottomY(particle.getXRef());
                        ParticleContainerLinkedCells::addParticle(particle);
                    }
                }
            }
            break;
        case BOTTOM:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    if (!particle.isGhostParticle) {
                        reflectPositionToGhostTopY(particle.getXRef());
                        ParticleContainerLinkedCells::addParticle(particle);
                    }
                }
            }
            break;
    }
    insertGhostParticles();
}

void PeriodicBoundaryCondition::insertGhostParticles() {
    switch (side) {
        case FRONT:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    std::array<double, 3> position = particle.getX();
                    reflectPositionToGhostBackZ(position);
                    ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                }
                //Here we do the reflection on the diagonal for the four front corners but only if all sides have periodic boundary conditions
                //left_bottom_front corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic && cell->getRelativePositionInDomain()[0] == 1 && cell->getRelativePositionInDomain()[1] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostTopY(position);
                        reflectPositionToGhostBackZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //right_bottom_front corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic && cell->getRelativePositionInDomain()[0] == ParticleContainerLinkedCells::numberCellsX - 2 &&
                    cell->getRelativePositionInDomain()[1] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostTopY(position);
                        reflectPositionToGhostBackZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //left_top_front corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic && cell->getRelativePositionInDomain()[0] == 1 &&
                    cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells::numberCellsY - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostBottomY(position);
                        reflectPositionToGhostBackZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //right_top_front corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic && cell->getRelativePositionInDomain()[0] == ParticleContainerLinkedCells::numberCellsX - 2 &&
                    cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells::numberCellsY - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostBottomY(position);
                        reflectPositionToGhostBackZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
            }
            break;
        case BACK:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    std::array<double, 3> position = particle.getX();
                    reflectPositionToGhostFrontZ(position);
                    ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                }

                //Here we do the reflection on the diagonal for the four back corners but only if all sides have periodic boundaries
                //left_bottom_back corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic &&
                cell->getRelativePositionInDomain()[0] == 1 && cell->getRelativePositionInDomain()[1] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostTopY(position);
                        reflectPositionToGhostFrontZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //right_bottom_back corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic &&
                cell->getRelativePositionInDomain()[0] == ParticleContainerLinkedCells::numberCellsX - 2 &&
                    cell->getRelativePositionInDomain()[1] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostTopY(position);
                        reflectPositionToGhostFrontZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //left_top_back corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic &&
                cell->getRelativePositionInDomain()[0] == 1 &&
                    cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells::numberCellsY - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostBottomY(position);
                        reflectPositionToGhostFrontZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //right_top_back corner
                if (isRightPeriodic && isBottomPeriodic && isFrontPeriodic &&
                cell->getRelativePositionInDomain()[0] == ParticleContainerLinkedCells::numberCellsX - 2 &&
                    cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells::numberCellsY - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostBottomY(position);
                        reflectPositionToGhostFrontZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
            }
            break;
        case RIGHT:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    std::array<double, 3> position = particle.getX();
                    reflectPositionToGhostLeftX(position);
                    ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                }
                //Here we do the reflection for the axis on the right side but only if the neighbouring sides have periodic boundaries
                //Right_Bottom_Edge
                if (isBottomPeriodic && cell->getRelativePositionInDomain()[1] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostTopY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Right_Top_Edge
                if (isBottomPeriodic && cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells::numberCellsY - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostBottomY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Right_Back_Edge
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostFrontZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Right_Front_Edge
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == ParticleContainerLinkedCells::numberCellsZ - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostLeftX(position);
                        reflectPositionToGhostBackZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
            }
            break;
        case LEFT:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    std::array<double, 3> position = particle.getX();
                    reflectPositionToGhostRightX(position);
                    ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                }
                //Here we do the reflection for all left edges but the neighbouring side has also to be periodic
                //Left_Bottom_Edge
                if (isBottomPeriodic && cell->getRelativePositionInDomain()[1] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostTopY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Left_Top_Edge
                if (isBottomPeriodic && cell->getRelativePositionInDomain()[1] == ParticleContainerLinkedCells::numberCellsY - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostBottomY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Left_Back_Edge
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostFrontZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Left_Front_Edge
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == ParticleContainerLinkedCells::numberCellsZ - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostRightX(position);
                        reflectPositionToGhostBackZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
            }
            break;
        case TOP:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    std::array<double, 3> position = particle.getX();
                    reflectPositionToGhostBottomY(position);
                    ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                }
                //Here we do the reflection for the remaining two top edges but the neighbouring sides have also to be periodic
                //Top_Back_Edge
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostFrontZ(position);
                        reflectPositionToGhostBottomY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Top_Front_Edge
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == ParticleContainerLinkedCells::numberCellsZ - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostBackZ(position);
                        reflectPositionToGhostBottomY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
            }
            break;
        case BOTTOM:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    std::array<double, 3> position = particle.getX();
                    reflectPositionToGhostTopY(position);
                    ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                }
                //Here we do the reflection for the remaining two bottom edges but the neighbouring sides have also to be periodic
                //Bottom_Back_Edge
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == 1) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostFrontZ(position);
                        reflectPositionToGhostTopY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
                //Bottom_Front_Edge the additional
                if (isFrontPeriodic && cell->getRelativePositionInDomain()[2] == ParticleContainerLinkedCells::numberCellsZ - 2) {
                    for (auto &particle: cell->getParticles()) {
                        std::array<double, 3> position = particle.getX();
                        reflectPositionToGhostBackZ(position);
                        reflectPositionToGhostTopY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM(), particle.getType());
                    }
                }
            }
            break;
    }
}

inline void PeriodicBoundaryCondition::reflectPositionToGhostRightX(std::array<double, 3> &position) {
    position[0] += ParticleContainerLinkedCells::domainSizeX;
}

inline void PeriodicBoundaryCondition::reflectPositionToGhostLeftX(std::array<double, 3> &position) {
    position[0] -= ParticleContainerLinkedCells::domainSizeX;
}

inline void PeriodicBoundaryCondition::reflectPositionToGhostTopY(std::array<double, 3> &position) {
    position[1] += ParticleContainerLinkedCells::domainSizeY;
}

inline void PeriodicBoundaryCondition::reflectPositionToGhostBottomY(std::array<double, 3> &position) {
    position[1] -= ParticleContainerLinkedCells::domainSizeY;
}

inline void PeriodicBoundaryCondition::reflectPositionToGhostFrontZ(std::array<double, 3> &position) {
    position[2] += ParticleContainerLinkedCells::domainSizeZ;
}

inline void PeriodicBoundaryCondition::reflectPositionToGhostBackZ(std::array<double, 3> &position) {
    position[2] -= ParticleContainerLinkedCells::domainSizeZ;
}
