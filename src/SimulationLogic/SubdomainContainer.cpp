//
// Created by thomas on 31.12.21.
//

#include "SubdomainContainer.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include "OutputWriter/CSVWriter.h"

void SubdomainContainer::generateSubdomains(const std::vector<int> &sizesXSubdomains,
                                             const std::vector<int> &sizesZSubdomains) {
    int currentPositionX = 0;
    int currentPositionZ = 0;

    int sizeSubdomainX;
    int sizeSubdomainY;
    int sizeSubdomainZ;
    int indexInDomain = 0;
    subdomains.resize(sizesXSubdomains.size() * sizesZSubdomains.size());
    sizeSubdomainY = ParticleContainerLinkedCells::numberCellsY;
    for (int i = 0; i < sizesXSubdomains.size(); ++i) {
        sizeSubdomainX = sizesXSubdomains[i];
        currentPositionZ = 0;
        for (int j = 0; j < sizesZSubdomains.size(); ++j) {
            sizeSubdomainZ = sizesZSubdomains[j];

            std::vector<SubdomainCell> *subdomainCells = new std::vector<SubdomainCell>(
                    sizeSubdomainX * sizeSubdomainY * sizeSubdomainZ);

            int counter = 0;
            for (int x = 0; x < sizeSubdomainX; ++x) {
                for (int z = 0; z < sizeSubdomainZ; ++z) {
                    for (int y = 0; y < sizeSubdomainY; ++y) {
                        indexInDomain = (currentPositionX + x) + (ParticleContainerLinkedCells::numberCellsX * y) +
                                ParticleContainerLinkedCells::numberCellsY * ParticleContainerLinkedCells::numberCellsX * (z + currentPositionZ);
                        auto &relativePositionInDomain = ParticleContainerLinkedCells::cells[indexInDomain].getRelativePositionInDomain();
                        bool cellIsSynchronizedBecauseOfX = (x == 0 || x == sizeSubdomainX - 1) && relativePositionInDomain[0] != 0 &&
                                relativePositionInDomain[0] != ParticleContainerLinkedCells::numberCellsX - 1;;
                        bool cellIsSynchronizedBecauseOfZ = (z == 0 || z == sizeSubdomainZ - 1) && relativePositionInDomain[2] != 0  &&
                                relativePositionInDomain[2] != ParticleContainerLinkedCells::numberCellsZ - 1;
                        bool cellIsSynchronized = cellIsSynchronizedBecauseOfX || cellIsSynchronizedBecauseOfZ;

                        if(cellIsSynchronized){
                            int sdfsd = 0;
                        }
                        (*subdomainCells)[counter] = SubdomainCell({x, y, z},
                                                                   &ParticleContainerLinkedCells::cells[indexInDomain],
                                                                   cellIsSynchronized);
                        counter++;
                    }
                }
            }
            Subdomain* subdomain = new Subdomain(subdomainCells, {sizeSubdomainX, sizeSubdomainY, sizeSubdomainZ},
                                                 {currentPositionX, 0, currentPositionZ});
            subdomains[i*sizesZSubdomains.size()+j] = subdomain;
            currentPositionZ += sizesZSubdomains[j];
        }
        currentPositionX += sizesXSubdomains[i];
    }
}

void SubdomainContainer::generateSubdomainsWithNumberOfThreads(int numberOfThreads) {
    std::vector<int> sizesXParts = {};
    std::vector<int> sizesZParts = {ParticleContainerLinkedCells::numberCellsZ};
    switch (numberOfThreads) {
        case 1:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 1, sizesXParts);
            break;
        case 2:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 2, sizesXParts);
            break;
        case 4:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 4, sizesXParts);
            break;
        case 6:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 6, sizesXParts);
            break;
        case 8:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 4, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 2, sizesZParts);
            break;
        case 12:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 6, sizesXParts);
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
        case 56:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 8, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 7, sizesZParts);
            break;
        case 64:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 8, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 8, sizesZParts);
            break;
        case 256:
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsX, 16, sizesXParts);
            splitInNearlyEqualParts(ParticleContainerLinkedCells::numberCellsZ, 16, sizesZParts);
            break;
    }
    generateSubdomains(sizesXParts, sizesZParts);
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



const std::vector<Subdomain *> &SubdomainContainer::getSubdomains() const {
    return subdomains;
}

void SubdomainContainer::writeNumberOfParticlesToFile(){
    std::string lineForCSVFile = "";
    std::string pathToCSVFile = XMLParser::pathToAnalysisFolder_p + "/NumberOfParticlesPerSubdomain.csv";
    int numberParticles = 0;
    for(auto& subdomain : subdomains){
        numberParticles = subdomain->countNumberOfParticles();
        lineForCSVFile += std::to_string(numberParticles) + ",";
    }
    CSVWriter writer = CSVWriter();
    writer.writeToFile(pathToCSVFile, lineForCSVFile);
}

void SubdomainContainer::writeHeaderFileForNumberParticles(){
    std::string pathToCSVFile = XMLParser::pathToAnalysisFolder_p + "/NumberOfParticlesPerSubdomain.csv";
    CSVWriter writer = CSVWriter();
    writer.createCSV(pathToCSVFile);
    std::string headerLine = "";

    int counter = 0;
    for(auto& subdomain : subdomains){
        headerLine += "Subdomain_" + std::to_string(counter) + ",";
        counter++;
    }
    writer.writeToFile(pathToCSVFile, headerLine);
}