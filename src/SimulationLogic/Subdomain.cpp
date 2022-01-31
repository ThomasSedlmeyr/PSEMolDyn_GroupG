#include "Subdomain.h"


Subdomain::Subdomain(std::vector<SubdomainCell> *cells, std::array<int, 3> dimensions,
                     std::array<int, 3> leftBottomBackPosition) : cells(
        cells), dimensions(dimensions), leftBottomBackPosition(leftBottomBackPosition) {}

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