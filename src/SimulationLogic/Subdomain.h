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
    Subdomain(std::vector<SubdomainCell> *cells, std::array<int, 3> dimensions, std::array<int, 3> leftBottomBackPosition);

    int getNumberParticles() const;

    void calculateF();

private:
    void calculateNumberOfParticles();


    void setSynchronizedSubdomainCells();


    bool checkIfOneValuesMatches(int value1, int value2, const std::array<int, 3> &array);
};

#endif //PSEMOLDYN_GROUPG_SUBDOMAIN_H
