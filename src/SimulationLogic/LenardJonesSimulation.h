//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_LENARDJONESSIMULATION_H
#define PSEMOLDYN_GROUPG_LENARDJONESSIMULATION_H

#include "Simulation.h"

class LenardJonesSimulation: Simulation{
    void calculateF() override;

private:
    //In dieser Klasse wird die Kraftberechnung überschrieben,damit der Particle Container die Kraft berechnen kann.
    double epsilon;
    double m;
    double rho;
};


#endif //PSEMOLDYN_GROUPG_LENARDJONESSIMULATION_H
