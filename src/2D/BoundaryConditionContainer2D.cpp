//
// Created by thomas on 30.11.21.
//

#include "BoundaryConditionContainer2D.h"
#include "OutFlowCondition2D.h"
#include "BoundaryConditions/ReflectingCondition.h"
#include "BoundaryConditions/BetterReflectingCondition.h"
#include "XML_Parser/XMLParser.h"
#include "BoundaryCondition2D.h"

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
                    //TODO bisher geht nur outflow
                case BoundaryCondition2D::REFLECTING_TYPE:
                    boundaryConditions[i] = reinterpret_cast<BoundaryCondition2D *>(new ReflectingCondition(
                            BoundaryCondition2D::REFLECTING_TYPE, i + 1, domainSize, XMLParser::rho_p));
                    break;
                case BoundaryCondition2D::BETTER_REFLECTION_TYPE:
                    boundaryConditions[i] = reinterpret_cast<BoundaryCondition2D *>(new BetterReflectingCondition(
                            BoundaryCondition2D::BETTER_REFLECTION_TYPE, i + 1));
            }
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