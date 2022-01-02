//
// Created by philip on 29.11.21.
//

#include "PosCalculationVisitor.h"

PosCalculationVisitor::PosCalculationVisitor(double deltaT) : delta_t(deltaT) {}

void PosCalculationVisitor::visitParticle(Particle &p) {
    if (p.getMovingAllowed()){
        auto &xRef = p.getXRef();
        xRef = xRef + delta_t * p.getV() + delta_t * delta_t / (2 * p.getM()) * p.getF();
    }
    p.prepareForNewForce();
}

void PosCalculationVisitor::setDeltaT(double deltaT) {
    delta_t = deltaT;
}

PosCalculationVisitor::PosCalculationVisitor() = default;
