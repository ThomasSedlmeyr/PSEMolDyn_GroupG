//
// Created by thomas on 31.12.21.
//

#ifndef PSEMOLDYN_GROUPG_SUBDOMAINCELL_H
#define PSEMOLDYN_GROUPG_SUBDOMAINCELL_H


#include "Cell.h"

class SubdomainCell {

public:
    SubdomainCell(Cell *pointerToCell, std::array<int, 3> relativePositionInSubdomain);
    SubdomainCell();
    SubdomainCell(const std::array<int, 3> &relativePositionInSubdomain, Cell *pointerToCell, bool isSynchronized);

private:
    std::array<int, 3> relativePositionInSubdomain;
    Cell* pointerToCell;
    bool isSynchronized = false;

public:
    [[nodiscard]] const std::array<int, 3> &getRelativePositionInSubdomain() const;

    Cell *getPointerToCell() const;

    [[nodiscard]] bool getIsSynchronized() const;
};


#endif //PSEMOLDYN_GROUPG_SUBDOMAINCELL_H
