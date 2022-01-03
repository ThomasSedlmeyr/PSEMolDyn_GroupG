/**
 * @brief Class that manages all Particles
 */
#pragma once
#include <vector>
#include <list>
#include "SimulationLogic/Particle.h"
#include "ParticleContainer.h"
#include <iterator>
#include <cstddef>
#include <functional>
#include <Visitors/ParticleVisitor.h>

class ParticleContainerDirectSum : public ParticleContainer{

private:
    /**
     * @brief vector containing all particles
     */
    std::vector<Particle> particles;

    std::vector<Particle *> particlesWithFZUp;


public:
    void updateParticlePositions(ParticleVisitor &visitor) override;

    void walkOverParticles(ParticleVisitor &visitor) override;

    void walkOverParticlePairs(ParticlePairVisitor &visitor) override;

    void addParticleToContainer(Particle &p) override;

    std::vector<Particle> &getParticles() override;

    void applyFZUp() override;
};
