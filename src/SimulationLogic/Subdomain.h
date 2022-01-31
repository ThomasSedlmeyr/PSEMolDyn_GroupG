//
// Created by thomas on 31.12.21.
//

#ifndef PSEMOLDYN_GROUPG_SUBDOMAIN_H
#define PSEMOLDYN_GROUPG_SUBDOMAIN_H


#include "Cell.h"
#include "SubdomainCell.h"

class Subdomain {
private:
    /**
     * @brief The dimensions in number of cells
     */
    std::vector<SubdomainCell>* cells;

    /**
     * @brief The dimensions in number of cells
     */
    std::array<int, 3> dimensions;

    /**
     * @brief The leftBottomFrontPosition of the Subdomain
     */
    std::array<int, 3> leftBottomBackPosition;

    /**
     * @brief the number of particles which are in the subdomain
     */
    int numberParticles;

public:
    /**
     * @brief the Constructor for Subdomain
     * @param cells the cells which were part of the subdomain
     * @param dimensions the dimensions of the subdomain
     * @param leftBottomBackPosition the left back position of the cell which is part of the Subdomain
     */
    Subdomain(std::vector<SubdomainCell> *cells, std::array<int, 3> dimensions, std::array<int, 3> leftBottomBackPosition);

    /**
     * @brief Counts the number of particles which are located in the subdomain
     * @return the number of particles
     */
    int countNumberOfParticles();

    std::vector<SubdomainCell> *getCells() const;
};

#endif //PSEMOLDYN_GROUPG_SUBDOMAIN_H
