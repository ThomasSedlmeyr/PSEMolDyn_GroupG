//
// Created by philip on 17.01.22.
//

#include "MeanVelocityVisitor.h"

void MeanVelocityVisitor::visitParticle(Particle &p) {
    numberOfParticles++;
    if (p.getMovingAllowed()){
        numberOfFlowParticles++;
        totalVelocity += p.getV()[1];
    }
}

double MeanVelocityVisitor::getMeanVelocity() const {
    return totalVelocity / numberOfFlowParticles;
}
int MeanVelocityVisitor::getNumberOfParticles() const {
    return numberOfParticles;
}

int MeanVelocityVisitor::getNumberOfFlowParticles() const {
    return numberOfFlowParticles;
}

void MeanVelocityVisitor::reset() {
    numberOfParticles = 0;
    numberOfFlowParticles = 0;
    totalVelocity = 0;
}

MeanVelocityVisitor::MeanVelocityVisitor() = default;
