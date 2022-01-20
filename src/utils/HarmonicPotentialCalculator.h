//
// Created by philip on 03.01.22.
//

#ifndef PSEMOLDYN_GROUPG_HARMONICPOTENTIALCALCULATOR_H
#define PSEMOLDYN_GROUPG_HARMONICPOTENTIALCALCULATOR_H

#include <iostream>
#include "SimulationLogic/Particle.h"
#include "GeometricObjects/Membrane.h"
#include "ArrayUtils.h"

inline void calculateHarmonicPotential(Particle &p1, Particle &p2){
    if (p1.getType() != p2.getType()){
        return;
    }
    if (Particle::particlesAreNeighbours(p1, p2)){
        auto diff = p2.getX()-p1.getX();
        auto norm = ArrayUtils::L2Norm(diff);
        double scalar;
        if (Particle::particlesAreDirectNeighbours(p1, p2)){
            scalar = k * (norm - rZero) * (1/norm);
        }else{
            scalar = k * (norm - sqrt(2) * rZero) * (1/norm);
        }
        double force;
        auto *f1 = &p1.getFRef();
        auto *f2 = &p2.getFRef();
        for (int i = 0; i < 3; ++i) {
            force = scalar * diff[i];
            #pragma omp atomic
            (*f1)[i] += force;
            #pragma omp atomic
            (*f2)[i] -= force;
        }
    }
};


#endif //PSEMOLDYN_GROUPG_HARMONICPOTENTIALCALCULATOR_H