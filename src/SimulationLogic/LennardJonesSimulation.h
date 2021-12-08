//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H
#define PSEMOLDYN_GROUPG_LENNARDJONESSIMULATION_H

#include "Simulation.h"
#include "GeometricObjects/Body.h"
#include <vector>
#include <gtest/gtest.h>
#include "Visitors/LJForceVisitor.h"

class LennardJonesSimulation: public Simulation{

private:
    /**
     * @brief Parameter for Lennard-Jones force calculation
     */
    double epsilon;
    /**
     * @brief Parameter for Lennard-Jones force calculation
     */
    double mass;
    /**
     * @brief Parameter for Lennard-Jones force calculation
     */
    double rho;
    /**
     * Implementation of the force calculation
     */
    LJForceVisitor forceCalcVisitor;

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