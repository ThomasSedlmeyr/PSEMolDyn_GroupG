//
// Created by philip on 16.12.21.
//

#include "VelScalingVisitor.h"

void VelScalingVisitor::visitParticle(Particle &p) {
    for (int i = 0; i < 2; ++i) {
        p.getVRef()[i] *= beta;
    }
}

void VelScalingVisitor::setBeta(double beta) {
    VelScalingVisitor::beta = beta;
}

VelScalingVisitor::VelScalingVisitor() = default;
