//
// Created by thomas on 30.11.21.
//

#include "BoundaryConditionContainer2D.h"
#include "OutFlowCondition2D.h"
#include "BoundaryConditions/ReflectingCondition.h"
#include "BetterReflectingCondition2D.h"
#include "XML_Parser/XMLParser.h"
#include "BoundaryCondition2D.h"
#include "PeriodicBoundaryCondition2D.h"

#include <utility>
namespace twoD {
    void BoundaryConditionContainer2D::calculateBoundaryConditions() {
        for (auto &boundaryCondition: boundaryConditions) {
            boundaryCondition->calculateBoundaryCondition();
        }
    }


    BoundaryConditionContainer2D::BoundaryConditionContainer2D(const std::array<int, 4> &boundaryConditionTypes,
                                                               int numberCellsInX,
                                                               int numberCellsInY,
                                                               std::array<double, 3> domainSize) :
            numberCellsInX(numberCellsInX),
            numberCellsInY(numberCellsInY),
            domainSize(domainSize) {

        for (std::size_t i = 0; i < boundaryConditionTypes.size(); i++) {
            switch (boundaryConditionTypes[i]) {
                case BoundaryCondition2D::OUTFLOW_TYPE:
                    boundaryConditions[i] = new OutFlowCondition2D(BoundaryCondition2D::OUTFLOW_TYPE, i + 1);
                    break;
                case BoundaryCondition2D::REFLECTING_TYPE:
                    std::cout << "Unimplemented boundary type\n";
                    exit(EXIT_FAILURE);
                case BoundaryCondition2D::BETTER_REFLECTION_TYPE:
                    boundaryConditions[i] = new BetterReflectingCondition2D(BoundaryCondition2D::BETTER_REFLECTION_TYPE, i + 1);
                    break;
                case BoundaryCondition::PERIODIC_BOUNDARY_TYPE:
                    boundaryConditions[i] = new PeriodicBoundaryCondition2D(BoundaryCondition2D::PERIODIC_BOUNDARY_TYPE, i + 1);
            }
        }
        //right, left, top, bottom
        if(boundaryConditionTypes[0] == BoundaryCondition2D::PERIODIC_BOUNDARY_TYPE){
            PeriodicBoundaryCondition2D::isRightPeriodic = true;
        }
        if(boundaryConditionTypes[3] == BoundaryCondition2D::PERIODIC_BOUNDARY_TYPE){
            PeriodicBoundaryCondition2D::isBottomPeriodic = true;
        }
    }

    const std::array<BoundaryCondition2D *, 4> &BoundaryConditionContainer2D::getBoundaryConditions() const {
        return boundaryConditions;
    }

    void BoundaryConditionContainer2D::doWorkAfterCalculationStep() {
        for (auto b: boundaryConditions) {
            b->doWorkAfterCalculationStep();
        }
    }
}