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
    std::array<double, 3> calculateFBetweenPair(Particle &p1, Particle &p2) override;
    bool readParticles(const std::string &filename) override;
    void setParamsWithValues() override;
    void initializeParamNames() override;
    bool readFile(std::vector<Particle> &particles, const std::string &fileName);
};


#endif //PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
