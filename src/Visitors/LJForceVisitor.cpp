//
// Created by philip on 29.11.21.
//

#include <iostream>
#include <cmath>
#include "LJForceVisitor.h"
#include "XML_Parser/BodyBuilder.h"
#include "utils/ArrayUtils.h"

LJForceVisitor::LJForceVisitor(double epsilon, double rho) : epsilon(epsilon), rho(rho) {}

std::vector<int> LJForceVisitor::membraneIDs{};

void LJForceVisitor::visitParticlePair(Particle &p1, Particle &p2) {
    const int &p1Type = p1.getType();
    const int &p2Type = p2.getType();
    rho = BodyBuilder::rhoLookUpTable[p1Type][p2Type];
    epsilon = BodyBuilder::epsilonLookUpTable[p1Type][p2Type];

    auto &x1 = p1.getX();
    auto &x2 = p2.getX();

    auto &f1 = p1.getFRef();
    auto &f2 = p2.getFRef();

    std::array<double, 3> diff{};
    double squaredNorm = 0;

    double singleDiff;
    for (int i = 0; i < 3; ++i) {
        singleDiff = x1[i] - x2[i];
        diff[i] = singleDiff;
        squaredNorm += singleDiff*singleDiff;
    }
    if (squaredNorm < 0.00001){
        std::cout << "suspiciously close\n";
    }

    //TODO this only works for one membrane!
    if (!membraneIDs.empty()){
        if (p1Type == membraneIDs[0] && p1Type == p2Type){
            //Makes sure that only the repulsive part of the LJ potential is applied
            auto threshold = pow(rho, 1.0 / 6);
            if (sqrt(squaredNorm) > threshold){
                return;
            }
        }
    }

    double term1 = -24.0*epsilon/squaredNorm;
    double term2 =  (rho*rho*rho*rho*rho*rho) / (squaredNorm * squaredNorm * squaredNorm);
    double term3 =  term2 - 2 * term2 * term2;
    double scalar = term1 * term3;

    for (double &d:diff) {
        d *= scalar;
    }
    //faster than using ArrayUtils
    double temp;
    for (int j = 0; j < 3; ++j) {
        temp = diff[j];
        f1[j] += temp;
        f2[j] -= temp;
    }
}

LJForceVisitor::LJForceVisitor() = default;