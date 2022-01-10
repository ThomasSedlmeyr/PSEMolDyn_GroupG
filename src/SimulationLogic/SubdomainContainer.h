//
// Created by thomas on 31.12.21.
//

#ifndef PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H
#define PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H


#include <vector>
#include "Subdomain.h"
#include "ComputationTask.h"

class SubdomainContainer {
private:
    int numberSubdomains;
    std::vector<Subdomain*> subdomains;
    std::vector<ComputationTask> computationTasks;


public:
    void generateSubdomains(int numberCellsX, int numberCellsY, int numberCellsZ);

    void generateComputationTasks(int numberOfTasks);

    void generateComputationTaskQueue();

    void generateComputationRowTasks(int numberOfTasks);

    [[nodiscard]] int getNumberSubdomains() const;

    [[nodiscard]] const std::vector<Subdomain *> &getSubdomains() const;

    [[nodiscard]] const std::vector<ComputationTask> &getComputationTasks() const;

    void generateSubdomainsWithNumberOfThreads(int numberOfThreads);

    void splitInNearlyEqualParts(int value, int numberOfParts, std::vector<int> &parts);

    void generateSubdomainsWithNumberOfThreads2(int numberOfThreads);

    void generateSubdomains2(const std::vector<int> &sizesXSubdomains, const std::vector<int> &sizesYSubdomains);
};




#endif //PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H
