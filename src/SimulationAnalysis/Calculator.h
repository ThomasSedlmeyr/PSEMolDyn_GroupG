#ifndef PSEMOLDYN_GROUPG_CALCULATOR_H
#define PSEMOLDYN_GROUPG_CALCULATOR_H


#include <vector>
#include "SimulationLogic/Particle.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include <string>

class Calculator {
protected:
    ParticleContainerLinkedCells particleContainer;
    std::vector<Particle> particles;
    void updateParticles();

public:
    virtual void calculationResultsToString() = 0;
    void appendLineToCSVFile(std::string& name);
    virtual ~Calculator();
};


#endif //PSEMOLDYN_GROUPG_CALCULATOR_H
