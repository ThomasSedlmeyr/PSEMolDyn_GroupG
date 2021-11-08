//
// Created by thomas on 05.11.21.
//

#ifndef PSEMOLDYN_GROUPG_CUBOID_H
#define PSEMOLDYN_GROUPG_CUBOID_H
#include "array"

class Body{
protected:
    /**
     * Position of the particle
     */
    std::array<double, 3> initialV;
    double meanVbrownianMotion;
    double meshWidth;
    double massPerParticle;
};


#endif //PSEMOLDYN_GROUPG_CUBOID_H
