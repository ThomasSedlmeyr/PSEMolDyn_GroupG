//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H
#define PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H

#include "Simulation.h"
#include "Body.h"
#include <vector>
class LennardJonesSimulation: Simulation{


private:
    //In dieser Klasse wird die Kraftberechnung überschrieben,damit der Particle Container die Kraft berechnen kann.
    double epsilon;
    double mass;
    double rho;
    double h;

    std::list<Body*> bodies;


    void calculateF();
    void readParticles(const std::string &filename) override;
    void setParamsWithValues() override;
    void initializeParamNames() override;

};



#endif //PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H
