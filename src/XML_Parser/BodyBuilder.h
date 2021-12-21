//
// Created by thomas on 18.12.21.
//

#ifndef PSEMOLDYN_GROUPG_BODYBUILDER_H
#define PSEMOLDYN_GROUPG_BODYBUILDER_H


#include <vector>
#include "GeometricObjects/Body.h"
#include "input.h"

class BodyBuilder {
public:
    static std::vector<std::vector<double>> rhoLookUpTable;
    static std::vector<std::vector<double>> epsilonLookUpTable;

    static bool buildBodies(std::list<Body*> &bodies, particlesLJ::body_sequence& bodySequence);

private:
    static void createLookUpTables(const std::vector<double> &valuesForLookUpRho,
                                   const std::vector<double> &valuesForLookUpEpsilon);

};


#endif //PSEMOLDYN_GROUPG_BODYBUILDER_H
