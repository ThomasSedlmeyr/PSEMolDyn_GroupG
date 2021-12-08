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
    /**
     * @brief Applies position update to given particle and prepares particle for force calculation
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


#endif //PSEMOLDYN_GROUPG_POSCALCULATIONVISITOR_H
