//
// Created by philip on 29.11.21.
//

#ifndef PSEMOLDYN_GROUPG_PARTICLEVISITOR_H
#define PSEMOLDYN_GROUPG_PARTICLEVISITOR_H


#include "utils/ArrayUtils.h"
#include "SimulationLogic/Particle.h"

class ParticleVisitor {
public:
    /**
     * @brief Arbitrary function to be applied to the Particle p
     * @param p
     */
    virtual void visitParticle(Particle &p) = 0;
};


#endif //PSEMOLDYN_GROUPG_PARTICLEVISITOR_H
