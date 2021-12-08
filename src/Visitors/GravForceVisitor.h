//
// Created by philip on 29.11.21.
//

#ifndef PSEMOLDYN_GROUPG_GRAVFORCEVISITOR_H
#define PSEMOLDYN_GROUPG_GRAVFORCEVISITOR_H


#include <SimulationLogic/Particle.h>
#include "ParticlePairVisitor.h"

class GravForceVisitor : public ParticlePairVisitor{
public:
    GravForceVisitor();
    /**
     * @brief Applies the gravitation force calculation to the given particle pair
     * @param p1
     * @param p2
     */
    void visitParticlePair(Particle &p1, Particle &p2) override;

};


#endif //PSEMOLDYN_GROUPG_GRAVFORCEVISITOR_H
