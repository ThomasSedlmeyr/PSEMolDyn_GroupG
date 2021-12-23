//
// Created by philip on 29.11.21.
//

#include "VelCalculationVisitor.h"

VelCalculationVisitor::VelCalculationVisitor(double deltaT) : delta_t(deltaT) {}

void VelCalculationVisitor::visitParticle(Particle &p) {
    p.setV(p.getV() + delta_t / (2 * p.getM()) * (p.getOldF() + p.getF()));
}

void VelCalculationVisitor::setDeltaT(double deltaT) {
    delta_t = deltaT;
}

VelCalculationVisitor::VelCalculationVisitor() = default;

