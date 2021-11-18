//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
#define PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H


#include "Simulation.h"

class GravitationSimulation : public Simulation {

private:
    void initializeParamNames() override;
    void setParamsWithValues() override;
    bool readFile(std::vector<Particle> &particles, const std::string &fileName);
    bool readParticles(const std::string &filename) override;
    std::array<double, 3> calculateFBetweenPair(Particle &p1, Particle &p2) override;
    void calculateFFast() override;

public:
    GravitationSimulation();
    virtual ~GravitationSimulation();
};


#endif //PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
