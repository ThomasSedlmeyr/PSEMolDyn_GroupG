//
// Created by thomas on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H
#define PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H


#include <vector>
#include "SimulationLogic/Particle.h"
#include "SimulationLogic/Cell.h"
#include "BoundaryCondition.h"

class ReflectingCondition : public BoundaryCondition {

protected:
    /**
     * @brief the ghost particles which were used to exert a force on the boundary particles
     */
    std::vector<Particle *> counterParticles;

    void calculateBoundaryCondition() override;

    void doWorkAfterCalculationStep() override;

public:
    /**
     * @brief this flag is used for debugging and testing. If this flag is that to true the ghost-particles
     * were not deleted.
     * @param isDebug
     */
    static bool isDebug;

    ReflectingCondition(int conditionType, int side, const std::array<double, 3> &domainSize);

private:

    std::array<double, 3> domainSize{};
    double rho = 0;

    /**
     * @brief Calculates the boundary condition for one cell
     * @param cell
     */
    void calculateBoundaryConditionForCell(Cell *cell);
};


#endif //PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H
