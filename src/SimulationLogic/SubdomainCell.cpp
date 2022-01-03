//
// Created by thomas on 31.12.21.
//

#include "SubdomainCell.h"

SubdomainCell::SubdomainCell(Cell *pointerToCell, std::array<int, 3> relativePositionInSubdomain)
        : pointerToCell(pointerToCell), relativePositionInSubdomain(relativePositionInSubdomain) {}

SubdomainCell::SubdomainCell() {}

const std::array<int, 3> &SubdomainCell::getRelativePositionInSubdomain() const {
    return relativePositionInSubdomain;
}

Cell *SubdomainCell::getPointerToCell() const {
    return pointerToCell;
}

SubdomainCell::SubdomainCell(const std::array<int, 3> &relativePositionInSubdomain, Cell *pointerToCell,
                             bool isSynchronized) : relativePositionInSubdomain(relativePositionInSubdomain),
                                                    pointerToCell(pointerToCell), isSynchronized(isSynchronized) {}
