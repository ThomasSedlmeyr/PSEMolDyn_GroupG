/**
 * @brief Class that manages all Particles
 */
#pragma once
#include <vector>
#include <list>
#include "Particle.h"
#include <iterator>
#include <cstddef>
#include <functional>

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

    //TODO delete?
    /**
     * test the fast force calculation compared to slower implementation
     * @return true if results of both calculations match
     */
    //bool testOptimizedFormula();

    void printParticles();

    /**
     * @brief applies f to all distinct pairs of particles to calculate new force
     * @param f function to apply to the pairs
     */
    void applyFToParticlePairs(const std::function<std::array<double, 3>(Particle&, Particle&)>& f);

private:
    std::vector<Particle> particles;

};
