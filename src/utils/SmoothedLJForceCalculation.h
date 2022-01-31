//
// Created by philip on 03.01.22.
//

#include <XML_Parser/BodyBuilder.h>
#include <XML_Parser/XMLParser.h>
#include <cmath>
#include "Visitors/LJForceVisitor.h"
#include "LJForceCalculation.h"


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


    double rl = XMLParser::crystallization_r_l_p;
    double rc = XMLParser::crystallization_r_c_p;
    double rcSquared = rc * rc;
    if(squaredNorm < rcSquared) {
        double rlSquared = rl * rl;
        double scalar = 0.0;
        double rhoPoweredBySix = rho*rho*rho*rho*rho*rho;
        double distancePoweredBySix = squaredNorm * squaredNorm * squaredNorm;
        double distance = sqrt(squaredNorm);

        if (squaredNorm <= rlSquared) {
            //Normal Lennard Jones-Caculation
            double term1 = -24.0 * epsilon / squaredNorm;
            double term2 = rhoPoweredBySix / distancePoweredBySix;
            double term3 = term2 - 2 * term2 * term2;
            scalar = term1 * term3;
            for (int i = 0; i < 3; ++i) {
                diff[i] *= scalar;
            }
        }else{
            double term2 = rc - rl;
            double term3 = term2 * term2 * term2;
            double term4 = -24.0 * rhoPoweredBySix  * epsilon / (term3 * distancePoweredBySix * distancePoweredBySix * squaredNorm );
            double term5 = rc - distance;
            scalar = term4 * term5 * (rcSquared * (2 * rhoPoweredBySix - distancePoweredBySix) +
                     rc * (3 * rl - distance) * (distancePoweredBySix - 2 * rhoPoweredBySix) +
                     distance *
                     (5 * rl * rhoPoweredBySix - 2 * rl * distancePoweredBySix - 3 * rhoPoweredBySix * distance +
                      distance * distancePoweredBySix));
            for (double &d: diff) {
                d *= -scalar;
            }
        }
    }else{
        diff = {0,0,0};
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
