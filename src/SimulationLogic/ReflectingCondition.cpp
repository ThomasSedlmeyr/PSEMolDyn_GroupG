#include <cmath>
#include "ReflectingCondition.h"
#include "ParticleContainerLinkedCells.h"

void ReflectingCondition::calculateBoundaryConditionForCell(Cell *cell) {
    deleteAllParticlesInHaloCells();
    switch(side)
    {
        case FRONT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectZtoBackCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint);
                }
            }
            break;
        case BACK:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectZtoFrontCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint);
                }
            }
            break;
        case RIGHT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectXtoLeftCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint);
                }
            }
            break;
        case LEFT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectXtoRightCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint);
                }
            }
            break;
        case TOP:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectYtoBottomCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint);
                }
            }
            break;
        case BOTTOM:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectYtoTopCell(cell->getParticles()[i].getX(), reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint);
                }
            }
            break;
    }
}

ReflectingCondition::ReflectingCondition(int conditionType, int side) : BoundaryCondition(conditionType, side) {

}

void ReflectingCondition::calculateBoundaryCondition() {
    for (auto& cell : specificHaloCells) {
        calculateBoundaryConditionForCell(cell);
    }
}

