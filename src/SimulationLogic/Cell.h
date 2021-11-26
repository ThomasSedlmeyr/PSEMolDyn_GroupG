//
// Created by thomas on 24.11.21.
//

#ifndef PSEMOLDYN_GROUPG_CELL_H
#define PSEMOLDYN_GROUPG_CELL_H


#include <vector>
#include <memory>
#include "Particle.h"

class Cell {

public:
    static const int INNER_CELL = 0;
    static const int BOUNDARY_CELL = 1;
    static const int HALO_CELL = 2;

    /**
     * all cells have the same size which is determined by the cutOffRadius
     */
    static double sizeX;
    static double sizeY;
    static double sizeZ;

    void calculateDimensions(double cutOffRadius);

    Cell(const std::vector<Particle> &particles, const std::array<double, 3> &position, int cellType);

    Cell(const std::array<double, 3> &position, int cellType);

    Cell();

private:
    std::vector<std::unique_ptr<Particle>> neighbours;

    std::vector<Particle> particles;
    /**
     * @brief position of left front side corner
     */
    std::array<double, 3> position;
    int cellType = INNER_CELL;

};


#endif //PSEMOLDYN_GROUPG_CELL_H
