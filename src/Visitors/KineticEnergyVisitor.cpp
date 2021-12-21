//
// Created by philip on 16.12.21.
//

#include "KineticEnergyVisitor.h"

void KineticEnergyVisitor::visitParticle(Particle &p) {
    numberOfParticles++;
    double scalarProduct = 0;
    for (int i = 0; i < 3; ++i) {
        scalarProduct += p.getV()[i] * p.getV()[i];
    }
    totalEnergy += p.getM() * scalarProduct / 2;
}

double KineticEnergyVisitor::getTotalEnergy() const {
    return totalEnergy;
}

void KineticEnergyVisitor::reset() {
    totalEnergy = 0;
    numberOfParticles = 0;
}

int KineticEnergyVisitor::getNumberOfParticles() const {
    return numberOfParticles;
}
