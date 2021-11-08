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
    void calculateF();
    void readInputFile(char *filename);
};


#endif //PSEMOLDYN_GROUPG_GRAVITATION_SIMULATION_H
