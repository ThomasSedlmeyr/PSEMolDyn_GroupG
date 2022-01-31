//
// Created by philip on 27.11.21.
//
#include <functional>
#include <Visitors/ParticleVisitor.h>
#include <Visitors/ParticlePairVisitor.h>

#ifndef PSEMOLDYN_GROUPG_PARTICLECONTAINER_H
#define PSEMOLDYN_GROUPG_PARTICLECONTAINER_H


class ParticleContainer {
private:

public:
    /**
     * @brief Constant values which describe the different types of ParticleContainer
     */
    static const int DIRECTSUM = 1;
    static const int LINKEDCELLS = 2;

    /**
     * @brief Updates the position for every particle using visitor
     * @param visitor Implementation of the position calculation
     */
    virtual void updateParticlePositions(ParticleVisitor &visitor) = 0;

    /**
     * @brief Iterates over all particles and applies the visitor to them
     * @param visitor
     */
    virtual void walkOverParticles(ParticleVisitor &visitor) = 0;

    /**
     * Iterates over all distinct particle pairs and applies the visitor to them
     * @param visitor
     */
    virtual void walkOverParticlePairs(ParticlePairVisitor &visitor) = 0;

    /**
     * @brief Returns all particles which are part of the ParticleContainer
     * @return the particles which are located in the ParticleContainer
     */
    virtual std::vector<Particle> & getParticles() = 0;

    /**
     * @brief Adds the given particle to the internal representation of the particles
     * @param p Particle to be added
     */
    virtual void addParticleToContainer(Particle &p) = 0;

    /**
     * @brief TODO Kommentar für Philip
     */
    virtual void applyFZUp() = 0;
};

#endif //PSEMOLDYN_GROUPG_PARTICLECONTAINER_H