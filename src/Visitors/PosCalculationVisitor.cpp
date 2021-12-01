//
// Created by philip on 29.11.21.
//

#include "PosCalculationVisitor.h"

PosCalculationVisitor::PosCalculationVisitor(double deltaT) : delta_t(deltaT) {}

void PosCalculationVisitor::visitParticle(Particle &p) {
    auto newPos = p.getX() + delta_t * p.getV() + pow(delta_t, 2) / (2 * p.getM()) * p.getF();
    p.setX(newPos);
    p.prepareForNewForce();
}

void PosCalculationVisitor::setDeltaT(double deltaT) {
    delta_t = deltaT;
}

PosCalculationVisitor::PosCalculationVisitor() = default;
