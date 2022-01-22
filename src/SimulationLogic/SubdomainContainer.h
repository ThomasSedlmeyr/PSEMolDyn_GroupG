//
// Created by thomas on 31.12.21.
//

#ifndef PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H
#define PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H


#include <vector>
#include "Subdomain.h"

class SubdomainContainer {
private:
    int numberSubdomains;
    std::vector<Subdomain*> subdomains;

public:
    [[nodiscard]] int getNumberSubdomains() const;

    [[nodiscard]] const std::vector<Subdomain *> &getSubdomains() const;

    static void splitInNearlyEqualParts(int value, int numberOfParts, std::vector<int> &parts);

    void generateSubdomainsWithNumberOfThreads(int numberOfThreads);

    void generateSubdomains(const std::vector<int> &sizesXSubdomains, const std::vector<int> &sizesZSubdomains);
};




#endif //PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H
