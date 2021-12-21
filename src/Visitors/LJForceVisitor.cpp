//
// Created by philip on 29.11.21.
//

#include "LJForceVisitor.h"
#include "XML_Parser/BodyBuilder.h"

LJForceVisitor::LJForceVisitor(double epsilon, double rho) : epsilon(epsilon), rho(rho) {}

void LJForceVisitor::visitParticlePair(Particle &p1, Particle &p2) {
    if (p1.getType() == -1 && p2.getType() == -1){
        return;
    }
    if (p1.getType() == -1){
        rho = BodyBuilder::rhoLookUpTable[p2.getType()][p2.getType()];
        epsilon = BodyBuilder::epsilonLookUpTable[p2.getType()][p2.getType()];
    }else if (p2.getType() == -1){
        rho = BodyBuilder::rhoLookUpTable[p1.getType()][p1.getType()];
        epsilon = BodyBuilder::epsilonLookUpTable[p1.getType()][p1.getType()];
    }else{
        rho = BodyBuilder::rhoLookUpTable[p1.getType()][p2.getType()];
        epsilon = BodyBuilder::epsilonLookUpTable[p1.getType()][p2.getType()];
    }

    auto &x1 = p1.getX();
    auto &x2 = p2.getX();
    std::array<double, 3> diff{};
    double squaredNorm = 0;

    double singleDiff;
    for (int i = 0; i < 3; ++i) {
        singleDiff = x1[i] - x2[i];
        diff[i] = singleDiff;
        squaredNorm += singleDiff*singleDiff;
    }

    double term1 = -24.0*epsilon/squaredNorm;
    double term2 =  (rho*rho*rho*rho*rho*rho) / (squaredNorm * squaredNorm * squaredNorm);
    double term3 =  term2 - 2 * term2 * term2;
    double scalar = term1 * term3;

    for (double &d:diff) {
        d *= scalar;
    }
    auto &f1 = p1.getFRef();
    auto &f2 = p2.getFRef();
    //faster than using ArrayUtils
    double temp;
    for (int j = 0; j < 3; ++j) {
        temp = diff[j];
        f1[j] += temp;
        f2[j] -= temp;
    }
}

LJForceVisitor::LJForceVisitor() = default;