//
// Created by thomas on 31.12.21.
//

#include <iostream>
#include "Subdomain.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

Subdomain::Subdomain(std::vector<SubdomainCell> *cells, std::array<int, 3> dimensions,
                     std::array<int, 3> leftBottomBackPosition) : cells(
        cells), dimensions(dimensions), leftBottomBackPosition(leftBottomBackPosition) {
    calculateNumberOfParticles();
}

void Subdomain::calculateNumberOfParticles() {
    numberParticles = 0;
    for (int i = 0; i < cells->size(); ++i) {
        numberParticles += (*cells)[i].getPointerToCell()->getParticles().size();
    }
}

int Subdomain::getNumberParticles() const {
    return numberParticles;
}

void Subdomain::setSynchronizedSubdomainCells() {

}

inline bool Subdomain::checkIfOneValuesMatches(int value1, int value2, const std::array<int, 3> &array) {
    for (int i = 0; i < array.size(); ++i) {
        if (array[i] == value1 || array[i] == value2) {
            return true;
        }
    }
    return false;
}

void Subdomain::calculateF() {

}

std::vector<SubdomainCell> *Subdomain::getCells() const {
    return cells;
}
