//
// Created by philip on 29.11.21.
//

#include "utils/ArrayUtils.h"
#include "GravForceVisitor.h"

void GravForceVisitor::visitParticlePair(Particle &p1, Particle &p2) {
    double normalizedDistance{ArrayUtils::L2Norm(p1.getX() - p2.getX())};
    double scalar{p1.getM() * p2.getM() / pow(normalizedDistance, 3)};
    std::array<double, 3> result {scalar * (p2.getX() - p1.getX())};
    auto &f1 = p1.getFRef();
    auto &f2 = p2.getFRef();
    //faster than using ArrayUtils
    double temp;
    for (int j = 0; j < 3; ++j) {
        temp = result[j];
        f1[j] += temp;
        f2[j] -= temp;
    }
}

GravForceVisitor::GravForceVisitor() = default;
