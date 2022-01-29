//
// Created by thomas on 31.12.21.
//

#ifndef PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H
#define PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H


#include <vector>
#include "Subdomain.h"

class SubdomainContainer {

private:
    /**
     * @brief the subdomains on which the SubdomainContainer operates on
     */
    std::vector<Subdomain*> subdomains;

public:

    /**
     * @brief return the subdomains on which the SubdomainContainer operates on
     * @return
     */
    [[nodiscard]] const std::vector<Subdomain *> &getSubdomains() const;

    /**
     * @brief Splits an integer in a certain number of parts. All parts have either the same size or
     * differ by one
     * @param value the value which should be split up
     * @param numberOfParts the number of parts in which value should be spilt up
     * @param parts the resulting array containing the split parts
     */
    static void splitInNearlyEqualParts(int value, int numberOfParts, std::vector<int> &parts);

    /**
     * @brief generates numberOfThread many processes
     * @param numberOfThreads the number of Subdomains which should be created
     */
    void generateSubdomainsWithNumberOfThreads(int numberOfThreads);

    /**
     * @brief create the the Subdomains with the given sizes. E.g. the first the Subdomain has the size
     * sizesXSubdomains[0] x sizesZSubdomains[0] x numberOfParticlesOfDomainInYDirection
     * @param sizesXSubdomains the sizes of the subdomains in x-direction
     * @param sizesZSubdomains the sizes of the subdomains in z-direction
     */
    void generateSubdomains(const std::vector<int> &sizesXSubdomains, const std::vector<int> &sizesZSubdomains);

    /**
     * @brief writes the header line to a csv-File containing the information of how many particles are located
     * in the subdomains
     */
    void writeHeaderFileForNumberParticles();

    /**
     * @brief appends the actual number of particles to a csv-File
     */
    void writeNumberOfParticlesToFile();
};




#endif //PSEMOLDYN_GROUPG_SUBDOMAINCONTAINER_H
