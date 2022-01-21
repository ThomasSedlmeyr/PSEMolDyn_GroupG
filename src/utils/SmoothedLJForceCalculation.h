//
// Created by philip on 03.01.22.
//

#include <XML_Parser/BodyBuilder.h>
#include <cmath>
#include "Visitors/LJForceVisitor.h"

const double threshholdFactor = pow(2, 1.0/6);

inline void calculateSmoothedLJForce(Particle &p1, Particle &p2, const std::array<double, 3>& pos1, const std::array<double, 3>& pos2, bool atomic) {
    std::array<double, 3> diff{};
    double squaredNorm = 0;

    double singleDiff;
    for (int i = 0; i < 3; ++i) {
        singleDiff = pos1[i] - pos2[i];
        diff[i] = singleDiff;
        squaredNorm += singleDiff*singleDiff;
    }

    const int &p1Type = p1.getType();
    const int &p2Type = p2.getType();
    double rho = BodyBuilder::rhoLookUpTable[p1Type][p2Type];
    double epsilon = BodyBuilder::epsilonLookUpTable[p1Type][p2Type];

    if (!LJForceVisitor::membraneIDs.empty()){
        if (p1Type == LJForceVisitor::membraneIDs[0] && p1Type == p2Type){
            //Makes sure that only the repulsive part of the LJ potential is applied
            auto threshold = rho * threshholdFactor;
            if (squaredNorm > threshold * threshold){
                return;
            }
        }
    }

    double rl;
    double rc;
    double rlSquared = rl * rl;
    double rcSquared = rc * rc;
    double scalar = 0.0;
    if(squaredNorm <= rlSquared){
        //Normal Lennard Jones-Caculation
        double term1 = -24.0*epsilon/squaredNorm;
        double term2 =  (rho*rho*rho*rho*rho*rho) / (squaredNorm * squaredNorm * squaredNorm);
        double term3 =  term2 - 2 * term2 * term2;
        scalar = term1 * term3;
    }
    else if(squaredNorm < rc){
        double rhoPoweredBySix = rho*rho*rho*rho*rho*rho;
        double distancePoweredBySix = squaredNorm * squaredNorm * squaredNorm;
        double distance = sqrt(squaredNorm);

        scalar = rcSquared*(2*rhoPoweredBySix-distancePoweredBySix) + rc * (3*rl-distance) * (distancePoweredBySix - 2*rhoPoweredBySix) +
                distance * (5 * rl * rhoPoweredBySix - 2 * rl * distancePoweredBySix - 3 * rhoPoweredBySix * distance + distance * distancePoweredBySix);
    }
    for (double &d:diff) {
        d *= scalar;
    }

    double temp;
    //faster than using ArrayUtils
    auto *f1 = &p1.getFRef();
    auto *f2 = &p2.getFRef();
    for (int j = 0; j < 3; ++j) {
        temp = diff[j];
        if (atomic){
            #pragma omp atomic
            (*f1)[j] += temp;
            #pragma omp atomic
            (*f2)[j] -= temp;
        }else{
            (*f1)[j] += temp;
            (*f2)[j] -= temp;
        }
    }
}
