#ifndef PSEMOLDYN_GROUPG_CALCULATOR_H
#define PSEMOLDYN_GROUPG_CALCULATOR_H


#include <vector>
#include "SimulationLogic/Particle.h"
#include "ParticleContainers/ParticleContainer.h"
#include <string>

class Calculator {
protected:
    ParticleContainer* particleContainer;
    std::vector<Particle> particles;
    void getSimulationParticles();

public:
    Calculator(ParticleContainer *particleContainer);

    virtual void calculationResultsToString() = 0;
    void appendLineToCSVFile(std::string& name);
    virtual ~Calculator();
};


#endif //PSEMOLDYN_GROUPG_CALCULATOR_H
