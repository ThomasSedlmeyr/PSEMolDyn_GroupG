//
// Created by philip on 17.12.21.
//

#include <iostream>
#include "Thermostat.h"

Thermostat::Thermostat(ParticleContainer *particleContainer, double targetTemp, int dimension, double maxDeltaT) : particleContainer(particleContainer), targetTemp(targetTemp), maxDeltaT(maxDeltaT), dimension(dimension){
    type = XMLParser::thermostatType_p;
}

void Thermostat::apply() {
    particleContainer->walkOverParticles(meanVelocityVisitor);
    auto numParticles = meanVelocityVisitor.getNumberOfParticles();
    auto meanVelocity = meanVelocityVisitor.getMeanVelocity();
    energyVisitor.setMeanVelocity(meanVelocity);
    particleContainer->walkOverParticles(energyVisitor);
    double currentTemp = energyVisitor.getTotalEnergy() / (double(numParticles) * dimension / 2);
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
    meanVelocityVisitor.reset();
    energyVisitor.reset();
}

Thermostat::Thermostat() = default;