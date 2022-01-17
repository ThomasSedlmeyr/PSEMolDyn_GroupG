//
// Created by philip on 17.01.22.
//

#ifndef PSEMOLDYN_GROUPG_MEANVELOCITYVISITOR_H
#define PSEMOLDYN_GROUPG_MEANVELOCITYVISITOR_H


#include "ParticleVisitor.h"

class MeanVelocityVisitor : public ParticleVisitor{
private:
    /**
     * @brief Total number of Particles involved in the simulation
     */
    int numberOfParticles{};
    double meanVelocity{};
public:
    void visitParticle(Particle &p) override;

    double getMeanVelocity() const;

    /**
     * @return Total number of Particles involved in the simulation
     */
    int getNumberOfParticles() const;

    /**
     * @brief Reset internal data
     */
    void reset();
};


#endif //PSEMOLDYN_GROUPG_MEANVELOCITYVISITOR_H
