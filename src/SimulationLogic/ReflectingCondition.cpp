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
                    std::array<double, 3> reflectedPoint;
                    cell->reflectZtoBackCell(reflectedPoint);
                    ParticleContainerLinkedCells::addGhostParticle(reflectedPoint);

                }
            }
            break;
        case BACK:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint;
                    cell->reflectZtoFrontCell(reflectedPoint);
                }
            }
            break;
        case RIGHT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint;
                    cell->reflectXtoLeftCell(reflectedPoint);
                }
            }
            break;
        case LEFT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint;
                    cell->reflectXtoRightCell(reflectedPoint);
                }
            }
            break;
        case TOP:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint;
                    cell->reflectYtoBottomCell(reflectedPoint);
                }
            }
            break;
        case BOTTOM:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                if (std::abs(cell->getParticles()[i].getX()[0]) < pow(2, 1 / 6)) {
                    std::array<double, 3> reflectedPoint;
                    cell->reflectYtoTopCell(reflectedPoint);
                }
            }
            break;
    }
}

ReflectingCondition::ReflectingCondition(int conditionType, int side, std::vector<Cell *> allBoundaryCells,
                                         std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY,
                                         int numberCellsInZ) : BoundaryCondition(conditionType, side, allBoundaryCells,
                                                                                 allHaloCells, numberCellsInX, numberCellsInY,
                                                                                 numberCellsInZ) {

}

