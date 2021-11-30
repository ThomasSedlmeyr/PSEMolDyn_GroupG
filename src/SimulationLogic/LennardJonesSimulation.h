//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H
#define PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H

#include "Simulation.h"
#include "Body.h"
#include <vector>
#include <gtest/gtest.h>
#include "Visitors/LJForceVisitor.h"

class LennardJonesSimulation: public Simulation{

private:
    double epsilon;
    double mass;
    double rho;
    double meshWidth;
    /**
     * Implementation of the force calculation
     */
    LJForceVisitor forceCalcVisitor;

    /**
     * @brief list of bodies relevant for the simulation
     */
    std::list<Body*> bodies;
    void initializeParamNames() override;
    void setParamsWithValues() override;
    bool readParticles(const std::string &filename) override;
    /**
     * @brief unites the particles from all bodies to single vector in particle container
     */
    void uniteParticlesFromBodies();
    //Allows test to access private method
    FRIEND_TEST(Tests, LennardJonesOptimization);
    void calculateF() override;

public:
    void setEpsilon(double epsilon);
    void setRho(double rho);
};



#endif //PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H
