//
// Created by philip on 03.01.22.
//

#include <XML_Parser/BodyBuilder.h>

const double threshholdFactor = pow(2, 1.0/6);

inline void calculateLJForce(Particle &p1, Particle &p2, const std::array<double, 3>& pos1, const std::array<double, 3>& pos2, bool atomic) {
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

    double term1 = -24.0*epsilon/squaredNorm;
    double term2 =  (rho*rho*rho*rho*rho*rho) / (squaredNorm * squaredNorm * squaredNorm);
    double term3 =  term2 - 2 * term2 * term2;
    double scalar = term1 * term3;

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
            #ifdef _OPENMP
            #pragma omp atomic
            #endif //_OPENMP
            (*f1)[j] += temp;
            #ifdef _OPENMP
            #pragma omp atomic
            #endif //_OPENMP
            (*f2)[j] -= temp;
        }else{
            (*f1)[j] += temp;
            (*f2)[j] -= temp;
        }
    }
}
