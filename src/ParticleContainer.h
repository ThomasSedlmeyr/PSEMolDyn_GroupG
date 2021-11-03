#ifndef PSEMOLDYN_GROUPG_PARTICLECONTAINER_H
#define PSEMOLDYN_GROUPG_PARTICLECONTAINER_H


#include <vector>
#include <list>
#include "Particle.h"

class ParticleContainer {
public:
    std::vector<Particle> &getParticles();
/**
 * plot the particles to a xyz-file
 */
    void plotParticles(int &iteration);
/**
 * calculate the force for all particles
 */
    void calculateF();

    void calculateFslower();

/**
 * calculate the position for all particles
 */
    void calculateX(const double &delta_t);

/**
 * calculate the position for all particles
 */
    void calculateV(const double &delta_t);

    bool testOptimizedFormula();

private:
    std::vector<Particle> particles;

};


#endif //PSEMOLDYN_GROUPG_PARTICLECONTAINER_H