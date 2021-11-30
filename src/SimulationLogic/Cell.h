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
    /**
     * contains a pointer to every neighbour cell
     */
    std::vector<Cell *> neighbourCells;

    /**
     * particles contained in the cell
     */
    std::vector<Particle> particles;

    /**
     * @brief position of left front side corner
     */
    std::array<double, 3> position;

    int cellType = INNER_CELL;

public:
    const std::array<double, 3> &getPosition() const;
    std::vector<Cell *> &getNeighbourCells();
    static const int getInnerCellValue();
    static const int getBoundaryCellValue();
    static const int getHaloCellValue();
    int getCellType() const;
    std::vector<Particle> &getParticles();
    void addCellToNeighbours(Cell *pCell);

    /**
     * Tests if cell is equal to another, based on position
     * @param other
     * @return whether cells are equal
     */
    bool operator==(Cell &other);

};


#endif //PSEMOLDYN_GROUPG_CELL_H
