//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_SIMULATION_H
#define PSEMOLDYN_GROUPG_SIMULATION_H


#include <outputWriter/Writer.h>
#include "ParticleContainer.h"
#include "Particle.h"

class Simulation {

protected:
    Particle particle1;
    ParticleContainer particleContainer;

private:
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

protected:
    virtual void calculateF();
    virtual void readInputFile(char *filename);


public:
    Simulation();
    virtual~Simulation();

    const ParticleContainer getParticleContainer() const;
    void calculateOneTimeStep(const int &delta_t);

    void simulate(const double &endTime, const int &delta_t, Writer &writer, const int &numberSkippedIterations,
             char *filename);
};


#endif //PSEMOLDYN_GROUPG_SIMULATION_H
