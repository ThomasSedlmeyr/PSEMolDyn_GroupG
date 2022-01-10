//
// Created by philip on 16.12.21.
//

#include "VelScalingVisitor.h"
#include "SimulationLogic/Thermostat.h"

void VelScalingVisitor::visitParticle(Particle &p) {
    if (type == Thermostat::REGULAR){
        for (int i = 0; i < 3; ++i) {
            p.getVRef()[i] *= beta;
        }
    }else{
        if (p.getMovingAllowed()){
            p.getVRef()[0] *= beta;
            p.getVRef()[2] *= beta;
        }
    }
}

void VelScalingVisitor::setBeta(double beta) {
    VelScalingVisitor::beta = beta;
}

VelScalingVisitor::VelScalingVisitor() = default;
