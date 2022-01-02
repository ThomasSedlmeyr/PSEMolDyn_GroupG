//
// Created by philip on 16.12.21.
//

#pragma once
#include "ParticleVisitor.h"

class ZGravVisitor : public ParticleVisitor{
private:
    /**
     * @brief Scaling factor
     */
    std::vector<int> particlesWithZGrav{};
public:
    /**
     * @brief Apply scaling to Particle
     * @param p
     */
    void visitParticle(Particle &p) override;

    void setParticlesWithZGrav(const std::vector<int> &particlesWithZGrav);
};


