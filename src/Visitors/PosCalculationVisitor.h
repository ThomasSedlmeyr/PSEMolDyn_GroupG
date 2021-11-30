//
// Created by philip on 29.11.21.
//

#ifndef PSEMOLDYN_GROUPG_POSCALCULATIONVISITOR_H
#define PSEMOLDYN_GROUPG_POSCALCULATIONVISITOR_H


#include "ParticleVisitor.h"

class PosCalculationVisitor : public ParticleVisitor{
public:
    PosCalculationVisitor();

    explicit PosCalculationVisitor(double deltaT);
    void visitParticle(Particle &p) override;
    void setDeltaT(double deltaT);

private:
    double delta_t{};
};


#endif //PSEMOLDYN_GROUPG_POSCALCULATIONVISITOR_H
