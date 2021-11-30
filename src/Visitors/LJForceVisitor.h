//
// Created by philip on 29.11.21.
//

#ifndef PSEMOLDYN_GROUPG_LJFORCEVISITOR_H
#define PSEMOLDYN_GROUPG_LJFORCEVISITOR_H


#include <SimulationLogic/Particle.h>
#include "ParticlePairVisitor.h"

class LJForceVisitor : public ParticlePairVisitor{
public:
    LJForceVisitor();
    LJForceVisitor(double epsilon, double rho);
    void visitParticlePair(Particle &p1, Particle &p2) override;
    void setEpsilon(double epsilon);
    void setRho(double rho);

private:
    /**
     * @brief Parameter for force calculation
     */
    double epsilon{};

    /**
     * @brief Parameter for force calculation
     */
    double rho{};
};


#endif //PSEMOLDYN_GROUPG_LJFORCEVISITOR_H
