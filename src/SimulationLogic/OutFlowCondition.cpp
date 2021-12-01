//
// Created by thomas on 30.11.21.
//

#include "OutFlowCondition.h"

void OutFlowCondition::calculateBoundaryCondition() {
    for (int i = 0; i < specificHaloCells.size(); ++i) {
        specificHaloCells[i]->getParticles().clear();
    }
}

OutFlowCondition::OutFlowCondition(int conditionType, int side, std::vector<Cell *> allBoundaryCells,
                                   std::vector<Cell *> allHaloCells, int numberCellsInX, int numberCellsInY,
                                   int numberCellsInZ) : BoundaryCondition(conditionType, side, allBoundaryCells,
                                                                           allHaloCells, numberCellsInX, numberCellsInY,
                                                                           numberCellsInZ) {

}
