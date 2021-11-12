//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
#define PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H


#include "Simulation.h"

class GravitationSimulation : public Simulation {
public:
    GravitationSimulation();
    virtual ~GravitationSimulation();


private:
    void calculateFslower();
    void calculateFold();
    void calculateF() override;
    void readParticles(const std::string &filename) override;
    void setParamsWithValues() override;
    void initializeParamNames() override;
    void readFile(std::vector<Particle> &particles, const std::string &fileName);
};


#endif //PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
