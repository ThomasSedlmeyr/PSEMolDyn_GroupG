//
// Created by thomas on 31.12.21.
//

#include "SubdomainContainer.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

void SubdomainContainer::generateSubdomains2(const std::vector<int> &sizesXSubdomains,
                                             const std::vector<int> &sizesZSubdomains) {
    int currentPositionX = 0;
    int currentPositionZ = 0;

    int sizeSubdomainX;
    int sizeSubdomainY;
    int sizeSubdomainZ;
    int indexInDomain = 0;
    subdomains.resize(sizesXSubdomains.size() * sizesZSubdomains.size());
    for (int i = 0; i < sizesXSubdomains.size(); ++i) {
        sizeSubdomainX = sizesXSubdomains[i];
        currentPositionZ = 0;
        for (int j = 0; j < sizesZSubdomains.size(); ++j) {
            sizeSubdomainY = ParticleContainerLinkedCells::numberCellsY;
            sizeSubdomainZ = sizesZSubdomains[j];

            std::vector<SubdomainCell> *subdomainCells = new std::vector<SubdomainCell>(
                    sizeSubdomainX * sizeSubdomainY * sizeSubdomainZ);

            int counter = 0;
            for (int x = 0; x < sizeSubdomainX; ++x) {
                for (int z = 0; z < sizeSubdomainZ; ++z) {
                    for (int y = 0; y < sizeSubdomainY; ++y) {
                        indexInDomain = currentPositionX + x + ParticleContainerLinkedCells::numberCellsY * y +
                                        ParticleContainerLinkedCells::numberCellsZ * (z + currentPositionZ);
                        auto &relativePositionInDomain = ParticleContainerLinkedCells::cells[indexInDomain].getRelativePositionInDomain();
                        bool cellIsSynchronized =
                                (x == 0 || x == sizeSubdomainX - 1 || y == 0 || y == sizeSubdomainY - 1 || z == 0 ||
                                 z == sizeSubdomainZ - 1) &&
                                //the borders of the domain have not to be synchronized
                                relativePositionInDomain[0] != 0 &&
                                relativePositionInDomain[1] != 0 &&
                                relativePositionInDomain[2] != 0 &&
                                relativePositionInDomain[0] != ParticleContainerLinkedCells::numberCellsX - 1 &&
                                relativePositionInDomain[1] != ParticleContainerLinkedCells::numberCellsY - 1 &&
                                relativePositionInDomain[2] != ParticleContainerLinkedCells::numberCellsZ - 1;

                        (*subdomainCells)[counter] = SubdomainCell({x, y, z},
                                                                   &ParticleContainerLinkedCells::cells[indexInDomain],
                                                                   cellIsSynchronized);
                        counter++;
                    }
                }
            }
            Subdomain *subdomain = new Subdomain(subdomainCells, {sizeSubdomainX, sizeSubdomainY, sizeSubdomainZ},
                                                 {currentPositionX, 0, currentPositionZ});
            subdomains[i*sizesZSubdomains.size()+j] = subdomain;
            currentPositionZ += sizesZSubdomains[j];
        }
        currentPositionX += sizesXSubdomains[i];
    }


}

void SubdomainContainer::generateSubdomains(int maxNumberCellsX, int maxNumberCellsY, int maxNumberCellsZ) {
    int numberSubdomainsX = (ParticleContainerLinkedCells::numberCellsX / maxNumberCellsX);
    int numberSubdomainsY = (ParticleContainerLinkedCells::numberCellsY / maxNumberCellsY);
    int numberSubdomainsZ = (ParticleContainerLinkedCells::numberCellsZ / maxNumberCellsZ);

    subdomains.resize(numberSubdomainsX * numberSubdomainsY * numberSubdomainsZ);
    int currentPositionX;
    int currentPositionY;
    int currentPositionZ;

    int sizeSubdomainX;
    int sizeSubdomainY;
    int sizeSubdomainZ;

    int counter = 0;
    for (int i = 0; i < numberSubdomainsZ; ++i) {
        sizeSubdomainZ = maxNumberCellsZ;
        //if we are at the front boundary
        if (i == numberSubdomainsZ) {
            sizeSubdomainZ = (ParticleContainerLinkedCells::numberCellsZ - maxNumberCellsZ * numberSubdomainsZ);
        }
        for (int j = 0; j < numberSubdomainsY; ++j) {
            sizeSubdomainY = maxNumberCellsY;
            if (j == numberSubdomainsY) {
                sizeSubdomainY = (ParticleContainerLinkedCells::numberCellsY - maxNumberCellsY * numberSubdomainsY);
            }
            for (int k = 0; k < numberSubdomainsX; ++k) {
                sizeSubdomainX = maxNumberCellsX;
                if (i == numberSubdomainsX) {
                    sizeSubdomainX = (ParticleContainerLinkedCells::numberCellsX - maxNumberCellsX * numberSubdomainsX);
                }
                //Now we create the Subdomain;
                int counter2 = 0;
                int indexInDomain = 0;
                std::vector<SubdomainCell> *subdomainCells = new std::vector<SubdomainCell>(
                        sizeSubdomainX * sizeSubdomainY * sizeSubdomainZ);

                for (int x = 0; x < sizeSubdomainX; ++x) {
                    currentPositionX = maxNumberCellsX * i + x;
                    for (int z = 0; z < sizeSubdomainZ; ++z) {
                        currentPositionZ = maxNumberCellsZ * z + z;
                        for (int y = 0; y < sizeSubdomainY; ++y) {
                            currentPositionY = maxNumberCellsY * j + y;
                            auto &relativePositionInDomain = ParticleContainerLinkedCells::cells[indexInDomain].getRelativePositionInDomain();
                            bool cellIsSynchronized =
                                    (x == 0 || x == sizeSubdomainX - 1 || y == 0 || y == sizeSubdomainY - 1 || z == 0 ||
                                     z == sizeSubdomainZ - 1) &&
                                    //the borders of the domain have not to be synchronized
                                    relativePositionInDomain[0] != 0 &&
                                    relativePositionInDomain[1] != 0 &&
                                    relativePositionInDomain[2] != 0 &&
                                    relativePositionInDomain[0] != numberSubdomainsX - 1 &&
                                    relativePositionInDomain[1] != numberSubdomainsY - 1 &&
                                    relativePositionInDomain[2] != numberSubdomainsZ - 1;
                            indexInDomain = x + ParticleContainerLinkedCells::numberCellsY * y +
                                            ParticleContainerLinkedCells::numberCellsZ * z;
                            (*subdomainCells)[counter2] = SubdomainCell({x, y, z},
                                                                        &ParticleContainerLinkedCells::cells[indexInDomain],
                                                                        cellIsSynchronized);
                            if (counter2 == 289) {
                                int sdf = z * sizeSubdomainZ + y * sizeSubdomainY + x;
                                int sdfs = 4;
                            }
                            counter2++;
                        }
                    }
                }
                Subdomain *subdomain = new Subdomain(subdomainCells, {sizeSubdomainX, sizeSubdomainY, sizeSubdomainZ},
                                                     {maxNumberCellsX * k, maxNumberCellsY * j, maxNumberCellsZ * i});
                subdomains[counter] = subdomain;
                counter++;
            }
        }
    }
}


void SubdomainContainer::generateSubdomainsWithNumberOfThreads(int numberOfThreads) {
    int maxNumberCellsX;
    int maxNumberCellsY;
    int maxNumberCellsZ;

    maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX;
    maxNumberCellsY = ParticleContainerLinkedCells::numberCellsY;
    maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ;
    switch (numberOfThreads) {
        case 2:
            maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 2;
            break;
        case 4:
            if (maxNumberCellsX >= 8) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 4;
            } else {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 2;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 2;
            }
            break;
        case 8:
            if (ParticleContainerLinkedCells::numberCellsX >= 16) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 8;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 8) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 4;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 2;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 4) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 2;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 4;
            }
            break;
        case 14:
            if (ParticleContainerLinkedCells::numberCellsX >= 28) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 14;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 14) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 7;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 2;
            } else {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 2;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 7;
            }
            break;
        case 16:
            if (ParticleContainerLinkedCells::numberCellsX >= 32) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 32;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 16) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 8;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 2;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 8) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 4;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 4;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 4) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 2;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 8;
            }
            break;

        case 28:
            if (ParticleContainerLinkedCells::numberCellsX >= 56) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 28;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 28) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 14;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 2;
            } else if (ParticleContainerLinkedCells::numberCellsX >= 14) {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 7;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 4;
            } else {
                maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX / 2;
                maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ / 14;
            }
            break;
    }
    generateSubdomains(maxNumberCellsX, maxNumberCellsY, maxNumberCellsZ);
}

void SubdomainContainer::generateSubdomainsWithNumberOfThreads2(int numberOfThreads) {
    int maxNumberCellsX;
    int maxNumberCellsY;
    int maxNumberCellsZ;

    maxNumberCellsX = ParticleContainerLinkedCells::numberCellsX;
    maxNumberCellsY = ParticleContainerLinkedCells::numberCellsY;
    maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ;

    std::vector<int> sizesXParts = {};
    std::vector<int> sizesZParts = {maxNumberCellsZ = ParticleContainerLinkedCells::numberCellsZ};
    switch (numberOfThreads) {
        case 2:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 2, sizesXParts);
            break;
        case 4:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 4, sizesXParts);
            break;
        case 8:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 4, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 2, sizesZParts);
            break;
        case 14:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 7, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 2, sizesZParts);
            break;
        case 16:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 8, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 2, sizesZParts);
            break;
        case 28:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 7, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 4, sizesZParts);
            break;
    }
    generateSubdomains2(sizesXParts, sizesZParts);
}


/**
 * Ich würde 3 mögliche vorgeben
 * Einmal mit einer fixen größe subdomains spezififzierbar
 * Einmal werden mehrere reihen gebündelt und zu einem task hinzugefügt
 * Einmal werden die Subdomains nach der Anzahl an Partikeln sortiert und der scheduler, nimmt ein
 * @param numberOfTasks
 */
void SubdomainContainer::generateComputationTasks(int numberOfTasks) {
    computationTasks = std::vector<ComputationTask>(numberOfTasks);

    for (int i = 0; i < subdomains.size(); ++i) {

    }
}

void SubdomainContainer::generateComputationTaskQueue() {
    computationTasks = std::vector<ComputationTask>(numberSubdomains);

    for (int i = 0; i < subdomains.size(); ++i) {
        std::vector<Subdomain *> subdomainsForTask = std::vector<Subdomain *>(1);
        subdomainsForTask[0] = subdomains[i];
        computationTasks[i] = ComputationTask(subdomainsForTask, i, subdomains[i]->getNumberParticles());
    }

    //sort in descending order
    std::sort(std::begin(computationTasks),
              std::end(computationTasks),
              [](const ComputationTask &ct1, const ComputationTask &ct2) {
                  return ct1.getNumberOfParticles() > ct2.getNumberOfParticles();
              });


}

void SubdomainContainer::splitInNearlyEqualParts(int value, int numberOfParts, std::vector<int> &parts) {
    int lowerSize = value / numberOfParts;
    int upperSize = lowerSize + 1;
    int numberRemainingValues = numberOfParts;

    parts.resize(numberOfParts);
    for (int i = 0; i < numberOfParts; i++) {
        //We fill the empty entries with the lowerSizeValue
        if (value / lowerSize == numberRemainingValues && value % lowerSize == 0) {
            parts[i] = lowerSize;
            value -= lowerSize;
        } else {
            parts[i] = upperSize;
            value -= upperSize;
        }
        numberRemainingValues--;
    }
}

void SubdomainContainer::generateComputationRowTasks(int numberOfTasks) {
    computationTasks = std::vector<ComputationTask>(numberOfTasks);

    for (int i = 0; i < subdomains.size(); ++i) {

    }
}

int SubdomainContainer::getNumberSubdomains() const {
    return numberSubdomains;
}

const std::vector<Subdomain *> &SubdomainContainer::getSubdomains() const {
    return subdomains;
}

const std::vector<ComputationTask> &SubdomainContainer::getComputationTasks() const {
    return computationTasks;
}