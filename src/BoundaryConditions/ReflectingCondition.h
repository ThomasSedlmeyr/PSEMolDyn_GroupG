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

public:

    ReflectingCondition(int conditionType, int side, const std::array<double, 3> &domainSize);

protected:
    std::vector<Particle *> counterParticles;

    void calculateBoundaryCondition() override;

    void doWorkAfterCalculationStep() override;

public:
    static bool isDebug;
public:
    static void setIsDebug(bool isDebug);

private:
    std::array<double, 3> domainSize{};

    void calculateBoundaryConditionForCell(Cell *cell);
};


#endif //PSEMOLDYN_GROUPG_REFLECTINGCONDITION_H
