//
// Created by thomas on 31.12.21.
//

#ifndef PSEMOLDYN_GROUPG_SUBDOMAINCELL_H
#define PSEMOLDYN_GROUPG_SUBDOMAINCELL_H


#include "Cell.h"

class SubdomainCell {

private:
    /**
     * @brief the relative position in the subdomain
     */
    std::array<int, 3> relativePositionInSubdomain;

    /**
     * @brief the pointer to the LinkedCell on which the SubdomainCell operates on
     */
    Cell* pointerToCell;

    /**
     * @brief This boolean indicates if we have to use atomic instructions when calculating
     * the force between the particles of this cell
     */
    bool isSynchronized = false;

public:
    SubdomainCell(Cell *pointerToCell, std::array<int, 3> relativePositionInSubdomain);
    SubdomainCell();
    SubdomainCell(const std::array<int, 3> &relativePositionInSubdomain, Cell *pointerToCell, bool isSynchronized);

    Cell *getPointerToCell() const;

    [[nodiscard]] bool getIsSynchronized() const;


};


#endif //PSEMOLDYN_GROUPG_SUBDOMAINCELL_H
