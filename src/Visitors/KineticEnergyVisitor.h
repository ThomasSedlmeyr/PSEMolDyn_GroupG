//
// Created by philip on 16.12.21.
//

#ifndef PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H
#define PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H

#include <XML_Parser/XMLParser.h>
#include "ParticleVisitor.h"

class KineticEnergyVisitor : public ParticleVisitor{
private:

    /**
     * @brief Total kinetic energy in the system
     */
    double totalEnergy{};

    /**
     * @brief Type of the thermostat
     */
    int type = XMLParser::thermostatType_p;

    double meanVelocity{};
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
     * @brief Reset internal data
     */
    void reset();

    void setMeanVelocity(double d);
};


#endif //PSEMOLDYN_GROUPG_KINETICENERGYVISITOR_H
