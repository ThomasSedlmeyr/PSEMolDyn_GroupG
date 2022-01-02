//
// Created by philip on 29.11.21.
//

#ifndef PSEMOLDYN_GROUPG_LJFORCEVISITOR_H
#define PSEMOLDYN_GROUPG_LJFORCEVISITOR_H


#include <SimulationLogic/Particle.h>
#include <vector>
#include "ParticlePairVisitor.h"

class LJForceVisitor : public ParticlePairVisitor{
public:
    LJForceVisitor();
    LJForceVisitor(double epsilon, double rho);
    /**
     * @brief Applies the Lennard-Jones force calculation to the given particle pair
     * @param p1
     * @param p2
     */
    void visitParticlePair(Particle &p1, Particle &p2) override;

    static std::vector<int> membraneIDs;

private:
    /**
     * @brief Parameter for force calculation
     */
    double epsilon{};

    /**
     * @brief Parameter for force calculation
     */
    double rho{};
};


#endif //PSEMOLDYN_GROUPG_LJFORCEVISITOR_H
