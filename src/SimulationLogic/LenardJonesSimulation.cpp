//
// Created by thomas on 07.11.21.
//

#include "LenardJonesSimulation.h"
#include "utils/ArrayUtils.h"

void LenardJonesSimulation::calculateF() {
    //TODO geht nicht wegen Referenzen?
    auto particles = particleContainer.getParticles();
    for (auto p1 = particles.begin(); p1 != particles.end(); ++p1){
        for (auto p2 = p1 + 1; p2 != particles.end(); ++p2){
            auto norm = ArrayUtils::L2Norm(p1->getX() - p2->getX());
            double term1 = -24*epsilon/pow(norm, 2);
            double term2 =  pow(rho/norm, 6);
            double term3 =  term2 - 2 * pow(term2, 2);
            auto result = term1 * term3 * (p2->getX() - p1->getX());
            p1->setOldF(p1->getF());
            p1->setF(p1->getF()+result);
            p2->setOldF(p2->getF());
            p2->setF(p2->getF()-result);
        }
    }
}
