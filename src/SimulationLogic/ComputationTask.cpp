//
// Created by thomas on 03.01.22.
//

#include "ComputationTask.h"

#include <utility>

int ComputationTask::getNumberOfParticles() const {
    return numberOfParticles;
}

ComputationTask::ComputationTask(std::vector<Subdomain *> subdomains, int id, int numberOfParticles)
        : subdomains(std::move(subdomains)), ID(id), numberOfParticles(numberOfParticles) {}

ComputationTask::ComputationTask() {}
