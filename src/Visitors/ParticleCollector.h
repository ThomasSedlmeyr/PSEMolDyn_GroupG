//
// Created by philip on 30.11.21.
//

#ifndef PSEMOLDYN_GROUPG_PARTICLECOLLECTOR_H
#define PSEMOLDYN_GROUPG_PARTICLECOLLECTOR_H


#include "ParticleVisitor.h"

class ParticleCollector : public ParticleVisitor{
private:
    std::vector<Particle> particles;
public:
    void visitParticle(Particle &p) override;
    std::vector<Particle> &getParticles();
};


#endif //PSEMOLDYN_GROUPG_PARTICLECOLLECTOR_H
