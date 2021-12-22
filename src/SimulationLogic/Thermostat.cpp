//
// Created by philip on 17.12.21.
//

#include <iostream>
#include "Thermostat.h"

Thermostat::Thermostat(ParticleContainer *particleContainer, double targetTemp, int dimensions, double maxDeltaT) : particleContainer(particleContainer), targetTemp(targetTemp), dimensions(dimensions), maxDeltaT(maxDeltaT){
}

void Thermostat::apply() {
    particleContainer->walkOverParticles(energyVisitor);
    double currentTemp = energyVisitor.getTotalEnergy() / (double(energyVisitor.getNumberOfParticles()) * dimensions / 2);
    //std::cout << "CurrentTemp: " << currentTemp << std::endl;
    double newTargetTemp;
    //limit update range to currentTemp +- maxDeltaT
    if (targetTemp >= currentTemp){
        newTargetTemp = std::min(targetTemp, currentTemp + maxDeltaT);
    }else{
        newTargetTemp = std::max(targetTemp, currentTemp - maxDeltaT);
    }
    double beta = sqrt(newTargetTemp/currentTemp);
    velScalingVisitor.setBeta(beta);
    particleContainer->walkOverParticles(velScalingVisitor);
    energyVisitor.reset();
}

Thermostat::Thermostat() = default;