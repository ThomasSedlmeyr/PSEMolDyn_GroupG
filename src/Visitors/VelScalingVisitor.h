//
// Created by philip on 16.12.21.
//

#ifndef PSEMOLDYN_GROUPG_VELSCALINGVISITOR_H
#define PSEMOLDYN_GROUPG_VELSCALINGVISITOR_H

#include "ParticleVisitor.h"

class VelScalingVisitor : public ParticleVisitor{
private:
    /**
     * @brief Scaling factor
     */
    double beta{};
public:
    VelScalingVisitor();
    /**
     * @brief Apply scaling to Particle
     * @param p
     */
    void visitParticle(Particle &p) override;
    void setBeta(double beta);
};


#endif //PSEMOLDYN_GROUPG_VELSCALINGVISITOR_H
