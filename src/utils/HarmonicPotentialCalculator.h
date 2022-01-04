//
// Created by philip on 03.01.22.
//

#ifndef PSEMOLDYN_GROUPG_HARMONICPOTENTIALCALCULATOR_H
#define PSEMOLDYN_GROUPG_HARMONICPOTENTIALCALCULATOR_H

#include "SimulationLogic/Particle.h"
#include "ArrayUtils.h"

//TODO parse from XML
double rZero = 2.2;
double k = 300;

inline void calculateHarmonicPotential(Particle &p1, Particle &p2){
    if (Particle::particlesAreNeighbours(p1, p2)){
        auto diff = p1.getXRef()-p2.getXRef();
        auto norm = ArrayUtils::L2Norm(diff);
        double scalar;
        if (Particle::particlesAreDirectNeighbours(p1, p2)){
            scalar = k * (norm - rZero) * (1/norm);
        }else{
            scalar = k * (norm - sqrt(2) * rZero) * (1/norm);
        }
        auto invertedDiff = -1 * diff;
        double force;
        auto &f1 = p1.getFRef();
        auto &f2 = p2.getFRef();
        for (int i = 0; i < 3; ++i) {
            force = scalar * invertedDiff[i];
            f1[i] += force;
            f2[i] -= force;
        }
    }
};


#endif //PSEMOLDYN_GROUPG_HARMONICPOTENTIALCALCULATOR_H