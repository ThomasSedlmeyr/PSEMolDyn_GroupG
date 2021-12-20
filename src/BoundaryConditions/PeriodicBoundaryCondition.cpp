//
// Created by thomas on 16.12.21.
//

#include "PeriodicBoundaryCondition.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

bool PeriodicBoundaryCondition::isDebug = false;

void PeriodicBoundaryCondition::doWorkAfterCalculationStep() {
    if (!PeriodicBoundaryCondition::isDebug) {
        deleteAllParticlesInHaloCells();
    }
}

void PeriodicBoundaryCondition::calculateBoundaryCondition() {
    switch (side) {
        case FRONT:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    haloCell->reflectZtoBackCell(particle.getXRef(), particle.getXRef());
                    ParticleContainerLinkedCells::reflectPositionInZ(particle.getXRef());
                    ParticleContainerLinkedCells::addParticle(particle);
                }
            }
            break;
        case BACK:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    haloCell->reflectZtoFrontCell(particle.getXRef(), particle.getXRef());
                    ParticleContainerLinkedCells::reflectPositionInZ(particle.getXRef());
                    ParticleContainerLinkedCells::addParticle(particle);
                }
            }
            break;
        case RIGHT:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    haloCell->reflectXtoLeftCell(particle.getXRef(), particle.getXRef());
                    ParticleContainerLinkedCells::reflectPositionInX(particle.getXRef());
                    ParticleContainerLinkedCells::addParticle(particle);
                }
            }
            break;
        case LEFT:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    reflectPositionToGhostRightX(particle.getXRef());
                    ParticleContainerLinkedCells::addParticle(particle);
                }
            }
            break;
        case TOP:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    haloCell->reflectYtoBottomCell(particle.getXRef(), particle.getXRef());
                    ParticleContainerLinkedCells::reflectPositionInY(particle.getXRef());
                    ParticleContainerLinkedCells::addParticle(particle);
                }
            }
            break;
        case BOTTOM:
            for (auto &haloCell: specificHaloCells) {
                for (auto &particle: haloCell->getParticles()) {
                    haloCell->reflectYtoTopCell(particle.getXRef(), particle.getXRef());
                    ParticleContainerLinkedCells::reflectPositionInY(particle.getXRef());
                    ParticleContainerLinkedCells::addParticle(particle);
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
                    //We do not want to reflect ghost Particles
                    if (particle.getId() != Particle::GHOST_TYPE) {
                        std::array<double, 3> position = particle.getX();
                        cell->reflectZtoFrontCell(position, position);
                        ParticleContainerLinkedCells::reflectPositionInZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM());
                    }
                }
            }
            break;
        case BACK:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    //We do not want to reflect ghost Particles
                    if (particle.getId() != Particle::GHOST_TYPE) {
                        std::array<double, 3> position = particle.getX();
                        cell->reflectZtoBackCell(position, position);
                        ParticleContainerLinkedCells::reflectPositionInZ(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM());
                    }
                }
            }
            break;
        case RIGHT:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    //We do not want to reflect ghost Particles
                    if (particle.getId() != Particle::GHOST_TYPE) {
                        std::array<double, 3> position = particle.getX();
                        cell->reflectXtoRightCell(position, position);
                        ParticleContainerLinkedCells::reflectPositionInX(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM());
                    }
                }
            }
            break;
        case LEFT:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    //We do not want to reflect ghost Particles
                    if (particle.getId() != Particle::GHOST_TYPE) {
                        std::array<double, 3> position = particle.getX();
                        cell->reflectXtoLeftCell(position, position);
                        ParticleContainerLinkedCells::reflectPositionInX(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM());
                    }
                }
            }
            break;
        case TOP:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    //We do not want to reflect ghost Particles
                    if (particle.getId() != Particle::GHOST_TYPE) {
                        std::array<double, 3> position = particle.getX();
                        cell->reflectYtoTopCell(position, position);
                        ParticleContainerLinkedCells::reflectPositionInY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM());
                    }
                }
            }
            break;
        case BOTTOM:
            for (auto &cell: specificBoundaryCells) {
                for (auto &particle: cell->getParticles()) {
                    //We do not want to reflect ghost Particles
                    if (particle.getId() != Particle::GHOST_TYPE) {
                        std::array<double, 3> position = particle.getX();
                        cell->reflectYtoBottomCell(position, position);
                        ParticleContainerLinkedCells::reflectPositionInY(position);
                        ParticleContainerLinkedCells::addGhostParticle(position, particle.getM());
                    }
                }
            }
            break;
    }
}


PeriodicBoundaryCondition::PeriodicBoundaryCondition(int conditionType, int side) : BoundaryCondition(conditionType,
                                                                                                      side) {
    addAdditionalNeighbours();
}

void PeriodicBoundaryCondition::addAdditionalNeighbours() {
    for (auto &specificBoundaryCell: specificBoundaryCells) {
        setNeighbourCell(specificBoundaryCell);
    }
}

void PeriodicBoundaryCondition::setNeighbourCell(Cell *cell) {
    std::array<std::array<int, 3>, 9> positionsOfNewNeighbours{};
    std::array<int, 3> positionOfPartnerCell = cell->getRelativePositionInDomain();
    switch (side) {
        case FRONT:

            break;
        case BACK:

            break;
        case RIGHT:

            break;
        case LEFT:
            positionOfPartnerCell[0] = ParticleContainerLinkedCells::numberCellsX - 2;
            //ParticleContainerLinkedCells::add9CellsAtRelativePositionsToNeighboursOfCell( ,positionOfPartnerCell);
            break;
        case TOP:

            break;
        case BOTTOM:

            break;
    }
}

inline void PeriodicBoundaryCondition::reflectPositionToGhostRightX(std::array<double, 3> &position) {
    position[0] += ParticleContainerLinkedCells::domainSizeX;
}
