//
// Created by thomas on 03.01.22.
//

#ifndef PSEMOLDYN_GROUPG_COMPUTATIONTASK_H
#define PSEMOLDYN_GROUPG_COMPUTATIONTASK_H


#include <vector>
#include "Subdomain.h"

class ComputationTask {


public:
    ComputationTask(std::vector<Subdomain *> subdomains, int id, int numberOfParticles);
    ComputationTask();

private:
    std::vector<Subdomain*> subdomains;
    int ID;
    int numberOfSynchronizedCells;
    int numberOfParticles;
public:
    int getNumberOfParticles() const;

    void runTask();
};


#endif //PSEMOLDYN_GROUPG_COMPUTATIONTASK_H
