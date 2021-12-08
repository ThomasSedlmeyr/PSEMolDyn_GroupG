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
    /**
     * @brief Applies velocity update to given particle
     * @param p
     */
    void visitParticle(Particle &p) override;
    /**
     * @brief Sets parameter deltaT for calculation
     * @param deltaT
     */
    void setDeltaT(double deltaT);

private:
    double delta_t{};
};


#endif //PSEMOLDYN_GROUPG_VELCALCULATIONVISITOR_H
