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
     * @brief Vector containing all particles
     */
    std::vector<Particle> particles;

    /**
     * @brief The particles on which a specific force in z-Direction is applied
     */
    std::vector<Particle *> particlesWithFZUp;

public:
    void updateParticlePositions(ParticleVisitor &visitor) override;

    void walkOverParticles(ParticleVisitor &visitor) override;

    void walkOverParticlePairs(ParticlePairVisitor &visitor) override;

    void addParticleToContainer(Particle &p) override;

    std::vector<Particle> &getParticles() override;

    void applyFZUp() override;
};
