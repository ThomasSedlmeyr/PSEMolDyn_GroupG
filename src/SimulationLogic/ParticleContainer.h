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

private:
    /**
     * @brief vector containing all particles
     */
    std::vector<Particle> particles;

public:

    /**
     * @brief applies f to all distinct pairs of particles to calculate new force
     * @param f function to apply to the pairs
     */
    void applyFToParticlePairs(const std::function<std::array<double, 3>(Particle&, Particle&)>& f);

    /**
     * @return vector of particles
     */
    std::vector<Particle> &getParticles();

    /**
     * @brief set particles to new vector
     * @param particles new particle vector
     */
    void setParticles(const std::vector<Particle> &particles);

};
