//
// Created by philip on 17.12.21.
//

#ifndef PSEMOLDYN_GROUPG_THERMOSTAT_H
#define PSEMOLDYN_GROUPG_THERMOSTAT_H


#include <Visitors/KineticEnergyVisitor.h>
#include <Visitors/VelScalingVisitor.h>
#include <ParticleContainers/ParticleContainer.h>

class Thermostat {
private:
    ParticleContainer *particleContainer{};
    double targetTemp{};
    double maxDeltaT{};
    int dimensions{};
    KineticEnergyVisitor energyVisitor{};
    VelScalingVisitor velScalingVisitor{};
public:
    Thermostat();
    Thermostat(ParticleContainer *particleContainer, double targetTemp, int dimensions, double maxDeltaT = 100000);

    void apply();
};


#endif //PSEMOLDYN_GROUPG_THERMOSTAT_H
