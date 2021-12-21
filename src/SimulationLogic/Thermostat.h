//
// Created by philip on 17.12.21.
//

#ifndef PSEMOLDYN_GROUPG_THERMOSTAT_H
#define PSEMOLDYN_GROUPG_THERMOSTAT_H


#include <cfloat>
#include <Visitors/KineticEnergyVisitor.h>
#include <Visitors/VelScalingVisitor.h>
#include <ParticleContainers/ParticleContainer.h>

class Thermostat {
private:
    ParticleContainer *particleContainer{};
    double targetTemp{};
    double maxDeltaT{};
    KineticEnergyVisitor energyVisitor{};
    VelScalingVisitor velScalingVisitor{};
public:
    Thermostat();
    Thermostat(ParticleContainer *particleContainer, double targetTemp, double maxDeltaT = DBL_MAX);

    void apply();
};


#endif //PSEMOLDYN_GROUPG_THERMOSTAT_H
