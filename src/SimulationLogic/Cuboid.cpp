//
// Created by thomas on 05.11.21.
//

#include "Cuboid.h"
Cuboid :: Cuboid(double leftFrontSideCornerX, double leftFrontSideCornerY, double leftFrontSideCornerZ,
                 double dimensionsX, double dimensionsY, double dimensionsZ){
    leftFrontSideCorner[0] = leftFrontSideCornerX;
    leftFrontSideCorner[1] = leftFrontSideCornerY;
    leftFrontSideCorner[2] = leftFrontSideCornerZ;

    dimensions[0] = dimensionsX;
    dimensions[1] = dimensionsY;
    dimensions[2] = dimensionsZ;


}