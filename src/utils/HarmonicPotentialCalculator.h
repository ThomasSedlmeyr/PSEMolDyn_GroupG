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
            scalar = k * (norm - rZero);
        }else{
            scalar = k * (norm - sqrt(2) * rZero);
        }
        double force;
        auto *f1 = &p1.getFRef();
        auto *f2 = &p2.getFRef();
        for (int i = 0; i < 3; ++i) {
            force = scalar * (diff[i] / norm);

            #ifdef _OPENMP
            #pragma omp atomic
            #endif //_OPENMP
            (*f1)[i] += force;
            #ifdef _OPENMP
            #pragma omp atomic
            #endif //_OPENMP
            (*f2)[i] -= force;
        }
    }
};


#endif //PSEMOLDYN_GROUPG_HARMONICPOTENTIALCALCULATOR_H