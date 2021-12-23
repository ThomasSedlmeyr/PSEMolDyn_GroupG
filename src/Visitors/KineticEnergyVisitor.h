//
// Created by philip on 16.12.21.
//

#ifndef PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H
#define PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H

#include "ParticleVisitor.h"

class KineticEnergyVisitor : public ParticleVisitor{
private:
    /**
     * @brief Total number of Particles involved in the simulation
     */
    int numberOfParticles{};

    /**
     * @brief Total kinetic energy in the system
     */
    double totalEnergy{};
public:
    /**
     * @brief Calculates the kinetic energy of single Particle and adds it to totalEnergy
     * @param p
     */
    void visitParticle(Particle &p) override;

    /**
     * @return Total kinetic energy in the system
     */
    double getTotalEnergy() const;

    /**
     * @return Total number of Particles involved in the simulation
     */
    int getNumberOfParticles() const;

    /**
     * @brief Reset internal data
     */
    void reset();
};


#endif //PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H
