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

    /**
     * @brief average density in bin
     */
    double density;

    /**
     * @brief particles that lie in bin
     */
    std::vector<Particle> particles;

public:
    /**
     * @brief getter for average velocity
     */
    [[nodiscard]] double getMeanVelocity() const;

    /**
     * @brief getter for average density
     */
    [[nodiscard]] double getDensity() const;

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
