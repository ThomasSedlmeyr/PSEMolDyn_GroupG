//
// Created by thomas on 30.11.21.
//

#include "ReflectingCondition.h"

void ReflectingCondition::calculateBoundaryConditionForCell(Cell *cell) {
    if(side == RIGHT || side == LEFT) {
        for (int i = 0; i < cell->getParticles().size(); ++i) {
            if(std::abs(cell->getParticles()[i].getX()[0]) < h){

            }
        }
    }
}

ReflectingCondition::ReflectingCondition(int conditionType, int side, std::vector<Cell *> allBoundaryCells,
                                   std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY,
                                   int numberCellsInZ) : BoundaryCondition(conditionType, side, allBoundaryCells,
                                                                           allHaloCells, numberCellsInX, numberCellsInY,
                                                                           numberCellsInZ) {

}
