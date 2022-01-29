#include "Subdomain.h"


Subdomain::Subdomain(std::vector<SubdomainCell> *cells, std::array<int, 3> dimensions,
                     std::array<int, 3> leftBottomBackPosition) : cells(
        cells), dimensions(dimensions), leftBottomBackPosition(leftBottomBackPosition) {}

inline bool Subdomain::checkIfOneValuesMatches(int value1, int value2, const std::array<int, 3> &array) {
    for (int i = 0; i < array.size(); ++i) {
        if (array[i] == value1 || array[i] == value2) {
            return true;
        }
    }
    return false;
}

std::vector<SubdomainCell> *Subdomain::getCells() const {
    return cells;
}

int Subdomain::countNumberOfParticles(){
    int numberOfParticles = 0;
    for(auto& cell : *cells){
        numberOfParticles += cell.getPointerToCell()->getParticles().size();
    }
    return numberOfParticles;
}