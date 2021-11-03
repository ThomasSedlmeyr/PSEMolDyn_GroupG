/**
 * @brief Class that manages all Particles
 */
#pragma once
#include <vector>
#include <list>
#include "Particle.h"

class ParticleContainer {
public:
    /**
     * @return vector of particles
     */
    std::vector<Particle> &getParticles();

    /**
    * @brief writes the actual information of the particles into a vtk file
    * @param iteration iteration in which the information of the particles were saved
    */
    void plotParticles(int &iteration);

    /**
    * @brief calculate the force for all particles
    */
    void calculateF();

    /**
    * @brief calculates the force for every particle in an easy but inefficient way
    */
    void calculateFslower();

    /**
    * @brief calculate the position for all particles
    * @param delta_t timestep to use for calculation
    */
    void calculateX(const double &delta_t);

    /**
    * @brief calculate the velocity for all particles
    * @param delta_t timestep to use for calculation
    */
    void calculateV(const double &delta_t);

    /**
     * test the fast force calculation compared to slower implementation
     * @return true if results of both calculations match
     */
    bool testOptimizedFormula();

private:
    std::vector<Particle> particles;

};
