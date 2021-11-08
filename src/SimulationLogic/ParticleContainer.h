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
    //void plotParticles(int &iteration);

    /**
    * @brief calculates the force for every particle in an easy but inefficient way
    */
    //std::array<double, 3> v; calculateFslower();

    /**
    * @brief calculate the force for all particles
    */
    //void calculateF();

    /**
     * test the fast force calculation compared to slower implementation
     * @return true if results of both calculations match
     */
    //bool testOptimizedFormula();
    void printParticles();
private:
    std::vector<Particle> particles;


};
