#ifndef PSEMOLDYN_GROUPG_BIN_H
#define PSEMOLDYN_GROUPG_BIN_H


#include <vector>
#include "SimulationLogic/Particle.h"

class Bin {
private:
    /**
     * @brief average velocity in bin
     */
    double meanVelocity;
public:
    /**
     * @brief getter for average velocity
     */
    double getMeanVelocity() const;

private:

    /**
     * @brief average density in bin
     */
    double density;
public:
    /**
     * @brief getter for average density
     */
    double getDensity() const;

private:

    /**
     * @brief particles that lie in bin
     */
    std::vector<Particle> particles;

public:

    /**
     * @brief calculate average density
     * @return average density
     */
    void calculateDensity();

    /**
     * @brief calculate average velocity
     * @return average velocity
     */
    void calculateVelocity();

    /**
     * @brief setter for particles
     * @param particles_ the particles to be set to
     */
    void setParticles(std::vector<Particle> particles_);
};


#endif //PSEMOLDYN_GROUPG_BIN_H
