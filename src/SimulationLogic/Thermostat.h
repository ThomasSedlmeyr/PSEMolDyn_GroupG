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

    /**
     * @brief ParticleContainer to use for thermostat
     */
    ParticleContainer *particleContainer{};

    /**
     * @brief Target temperature, read from XML-File
     */
    double targetTemp{};

    /**
     * @brief Maximum temperature change for one scaling step
     */
    double maxDeltaT{};

    /**
     * @brief Dimension to use for calculation(2 for 2D, 3 for 3D)
     */
    int dimension{};

    /**
     * @brief Visitor that calculates total kinetic energy in system
     */
    KineticEnergyVisitor energyVisitor{};

    /**
     * @brief Visitor that scales all velocities by a scaling factor
     */
    VelScalingVisitor velScalingVisitor{};
public:
    Thermostat();
    Thermostat(ParticleContainer *particleContainer, double targetTemp, int dimension, double maxDeltaT = 100000);

    /**
     * @brief Applies the thermostat once
     */
    void apply();
};


#endif //PSEMOLDYN_GROUPG_THERMOSTAT_H
