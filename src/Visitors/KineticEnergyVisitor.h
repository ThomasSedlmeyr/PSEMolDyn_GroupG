//
// Created by philip on 16.12.21.
//

#ifndef PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H
#define PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H

#include "ParticleVisitor.h"

class KineticEnergyVisitor : public ParticleVisitor{
private:
    int numberOfParticles{};
    double totalEnergy{};
public:
    void visitParticle(Particle &p) override;
    double getTotalEnergy() const;

    int getNumberOfParticles() const;

    void reset();
};


#endif //PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H
