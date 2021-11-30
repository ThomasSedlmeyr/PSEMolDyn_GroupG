//
// Created by philip on 29.11.21.
//

#ifndef PSEMOLDYN_GROUPG_VELCALCULATIONVISITOR_H
#define PSEMOLDYN_GROUPG_VELCALCULATIONVISITOR_H


#include "ParticleVisitor.h"

class VelCalculationVisitor : public ParticleVisitor{
public:
    VelCalculationVisitor();

    explicit VelCalculationVisitor(double deltaT);
    void visitParticle(Particle &p) override;
    void setDeltaT(double deltaT);

private:
    double delta_t{};
};


#endif //PSEMOLDYN_GROUPG_VELCALCULATIONVISITOR_H
