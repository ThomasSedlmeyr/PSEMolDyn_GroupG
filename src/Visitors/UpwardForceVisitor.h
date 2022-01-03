//
// Created by philip on 16.12.21.
//

#pragma once
#include "ParticleVisitor.h"

class UpwardForceVisitor : public ParticleVisitor{
public:
    /**
     * @brief The particle IDs for which the gravitation along the z-axis should be applied
     */
    static std::vector<int> particlesWithFZUp;

    static double fZUp;
    /**
     * @brief Apply Fz to p
     * @param p
     */
    void visitParticle(Particle &p) override;

};


