//
// Created by thomas on 03.01.22.
//

#include "ComputationTask.h"
#include "SubdomainContainer.h"

#include <utility>

void ComputationTask::runTask(){
    SubdomainContainer subdomainContainer = SubdomainContainer();
    subdomainContainer.generateComputationTasks(4);
    for(auto& subdomain : subdomains){
        subdomain->calculateF();
    }
}


int ComputationTask::getNumberOfParticles() const {
    return numberOfParticles;
}

ComputationTask::ComputationTask(std::vector<Subdomain *> subdomains, int id, int numberOfParticles)
        : subdomains(std::move(subdomains)), ID(id), numberOfParticles(numberOfParticles) {}

ComputationTask::ComputationTask() {}
