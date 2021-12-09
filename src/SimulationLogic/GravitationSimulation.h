//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
#define PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H


#include "Simulation.h"
#include "Visitors/GravForceVisitor.h"

class GravitationSimulation : public Simulation {

private:
    /**
     * @brief Implementation of the force calculation
     */
    GravForceVisitor forceCalcVisitor;
    bool readFile(const std::string &fileName);
    bool readParticles(const std::string &filename) override;
    void calculateF() override;

public:
    GravitationSimulation();
    ~GravitationSimulation() override;
};


#endif //PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
