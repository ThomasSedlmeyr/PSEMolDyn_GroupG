//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H
#define PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H

#include "Simulation.h"
#include "Body.h"
#include <vector>
#include <gtest/gtest.h>
class LennardJonesSimulation: public Simulation{


private:
    double epsilon;
    double mass;
    double rho;
    double meshWidth;
    std::list<Body*> bodies;
    FRIEND_TEST(Tests, LennardJonesOptimization);
    std::array<double, 3> calculateFBetweenPair(Particle &p1, Particle &p2) override;
    bool readParticles(const std::string &filename) override;
    void setParamsWithValues() override;
    void initializeParamNames() override;
    void generateAllParticles();

public:
    void setEpsilon(double epsilon);

    void setRho(double rho);
};



#endif //PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H
