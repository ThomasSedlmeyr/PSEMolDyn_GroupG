//
// Created by thomas on 05.11.21.
//

#ifndef PSEMOLDYN_GROUPG_RECTANGE_CUBOID_H
#define PSEMOLDYN_GROUPG_RECTANGE_CUBOID_H

#include "array"
#include "Body.h"
#include "Cuboid.h"

class Cuboid: public Body {
private:
    Cuboid(double leftFrontSideCornerX, double leftFrontSideCornerY, double leftFrontSideCornerZ, double dimensionsX,
           double dimensionsY, double dimensionsZ);

    std::array<double, 3> leftFrontSideCorner;
    std::array<double, 3> dimensions;

public:

};


#endif //PSEMOLDYN_GROUPG_RECTANGE_CUBOID_H
