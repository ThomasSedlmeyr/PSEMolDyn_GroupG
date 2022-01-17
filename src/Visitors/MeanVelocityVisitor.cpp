//
// Created by philip on 17.01.22.
//

#include "MeanVelocityVisitor.h"

void MeanVelocityVisitor::visitParticle(Particle &p) {
    numberOfParticles++;
    meanVelocity += p.getV()[1];
}

double MeanVelocityVisitor::getMeanVelocity() const {
    return meanVelocity / numberOfParticles;
}
int MeanVelocityVisitor::getNumberOfParticles() const {
    return numberOfParticles;
}

void MeanVelocityVisitor::reset() {
    numberOfParticles = 0;
}
