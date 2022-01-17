//
// Created by philip on 16.12.21.
//

#include "KineticEnergyVisitor.h"

void KineticEnergyVisitor::visitParticle(Particle &p) {
    double scalarProduct = 0;
    if (type == 0){
        for (int i = 0; i < 3; ++i) {
            scalarProduct += p.getV()[i] * p.getV()[i];
        }
    }else{
        scalarProduct += p.getV()[0] * p.getV()[0];
        scalarProduct += (p.getV()[1] - meanVelocity) * (p.getV()[1] - meanVelocity);
        scalarProduct += p.getV()[2] * p.getV()[2];
    }
    totalEnergy += p.getM() * scalarProduct / 2;
}

double KineticEnergyVisitor::getTotalEnergy() const {
    return totalEnergy;
}

void KineticEnergyVisitor::reset() {
    totalEnergy = 0;
}

void KineticEnergyVisitor::setMeanVelocity(double d) {
    meanVelocity = d;
}

