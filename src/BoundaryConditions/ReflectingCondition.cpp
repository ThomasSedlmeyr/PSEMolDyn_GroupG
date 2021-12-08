#include <cmath>
#include "ReflectingCondition.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

bool ReflectingCondition::isDebug = false;

void ReflectingCondition::calculateBoundaryConditionForCell(Cell *cell) {
    switch (side) {
        case FRONT:
            for (std::size_t i = 0; i < cell->getParticles().size(); ++i) {
                if (domainSize[2] - cell->getParticles()[i].getX()[2] < pow(2, 1.0 / 6)*rho) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectZtoFrontCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint, cell->getParticles()[i].getM());
                }
            }
            break;
        case BACK:
            for (std::size_t i = 0; i < cell->getParticles().size(); ++i) {
                if (cell->getParticles()[i].getX()[2] < pow(2, 1.0 / 6)*rho) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectZtoBackCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint, cell->getParticles()[i].getM());
                }
            }
            break;
        case RIGHT:
            for (std::size_t i = 0; i < cell->getParticles().size(); ++i) {
                if (domainSize[0] - cell->getParticles()[i].getX()[0] < pow(2, 1.0 / 6)*rho) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectXtoRightCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint, cell->getParticles()[i].getM());
                }
            }
            break;
        case LEFT:
            for (std::size_t i = 0; i < cell->getParticles().size(); ++i) {
                if (cell->getParticles()[i].getX()[0] < pow(2, 1.0 / 6)*rho) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectXtoLeftCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint, cell->getParticles()[i].getM());
                }
            }
            break;
        case TOP:
            for (std::size_t i = 0; i < cell->getParticles().size(); ++i) {
                if (domainSize[1] - cell->getParticles()[i].getX()[1] < pow(2, 1.0 / 6)*rho) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectYtoTopCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint, cell->getParticles()[i].getM());
                }
            }
            break;
        case BOTTOM:
            for (std::size_t i = 0; i < cell->getParticles().size(); ++i) {
                if (cell->getParticles()[i].getX()[1] < pow(2, 1.0 / 6)*rho) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectYtoBottomCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint, cell->getParticles()[i].getM());
                }
            }
            break;
    }
}

void ReflectingCondition::calculateBoundaryCondition() {
    for (auto& cell : specificBoundaryCells) {
        calculateBoundaryConditionForCell(cell);
    }
}

ReflectingCondition::ReflectingCondition(int conditionType, int side, const std::array<double, 3> &domainSize, double rhoArg)
        : BoundaryCondition(conditionType, side), domainSize(domainSize) {
    rho = rhoArg;
}

void ReflectingCondition::doWorkAfterCalculationStep() {
    if (!ReflectingCondition::isDebug) {
        deleteAllParticlesInHaloCells();
    }
}
