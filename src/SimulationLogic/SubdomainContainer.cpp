//
// Created by thomas on 31.12.21.
//

#include "SubdomainContainer.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

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
                std::vector<SubdomainCell>* subdomainCells = new std::vector<SubdomainCell>(sizeSubdomainX * sizeSubdomainY * sizeSubdomainZ);
                for (int z = 0; z < sizeSubdomainZ; ++z) {
                    currentPositionZ = maxNumberCellsZ * z + z;
                    for (int y = 0; y < sizeSubdomainY; ++y) {
                        currentPositionY = maxNumberCellsY * j + y;
                        for (int x = 0; x < sizeSubdomainX; ++x) {
                            currentPositionX = maxNumberCellsX * i + x;
                            bool cellIsSynchronized = x==0 || x == sizeSubdomainX-1 || y==0 || y == sizeSubdomainY-1 || z==0 || z == sizeSubdomainZ-1;
                            indexInDomain = x + ParticleContainerLinkedCells::numberCellsY * y  + ParticleContainerLinkedCells::numberCellsZ * z;
                            (*subdomainCells)[counter2] = SubdomainCell({x,y,z}, &ParticleContainerLinkedCells::cells[indexInDomain],  cellIsSynchronized);
                            if(counter2 == 289){
                                int sdf = z * sizeSubdomainZ + y * sizeSubdomainY + x;
                                int sdfs = 4;
                            }
                            counter2++;
                        }
                    }
                }
                Subdomain* subdomain = new Subdomain(subdomainCells, {sizeSubdomainX, sizeSubdomainY, sizeSubdomainZ},{maxNumberCellsX * k, maxNumberCellsY * j, maxNumberCellsZ * i});
                subdomains[counter] = subdomain;
                counter++;
            }
        }
    }
}



/**
 * Ich würde 3 mögliche vorgeben
 * Einmal mit einer fixen größe subdomains spezififzierbar
 * Einmal werden mehrere reihen gebündelt und zu einem task hinzugefügt
 * Einmal werden die Subdomains nach der Anzahl an Partikeln sortiert und der scheduler, nimmt ein
 * @param numberOfTasks
 */
void SubdomainContainer::generateComputationTasks(int numberOfTasks){
    computationTasks = std::vector<ComputationTask>(numberOfTasks);

    for (int i = 0; i < subdomains.size(); ++i) {

    }
}

void SubdomainContainer::generateComputationTaskQueue(){
    computationTasks = std::vector<ComputationTask>(numberSubdomains);

    for (int i = 0; i < subdomains.size(); ++i) {
        std::vector<Subdomain*> subdomainsForTask = std::vector<Subdomain*> (1);
        subdomainsForTask[0] = subdomains[i];
        computationTasks[i] = ComputationTask(subdomainsForTask, i, subdomains[i]->getNumberParticles());
    }

    //sort in descending order
    std::sort(std::begin(computationTasks),
              std::end(computationTasks),
              [](const ComputationTask &ct1, const ComputationTask &ct2) { return ct1.getNumberOfParticles() > ct2.getNumberOfParticles(); });


}

void SubdomainContainer::generateComputationRowTasks(int numberOfTasks){
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