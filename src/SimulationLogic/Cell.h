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

    /**
     * @brief the right boundary of the cell
     */
    double xBoundary;
    /**
     *@brief the top boundary of the cell
     */
    double yBoundary;
    /**
     * @brief the front boundary of the cell
     */
    double zBoundary;

    void calculateDimensions(double cutOffRadius);

    Cell(std::vector<Particle> particles, const std::array<double, 3> &position, int cellType);

    Cell(std::vector<Particle> particles, const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType);

    Cell(const std::array<double, 3> &position, int cellType);

    Cell(const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType);

    Cell();

    const std::array<int, 3> &getRelativePositionInDomain() const;

private:
    std::array<int, 3> relativePositionInDomain;
    /**
     * contains a pointer to every neighbour cell
     */
    std::vector<Cell*> neighbourCells;

    /**
     * particles contained in the cell
     */
    std::vector<Particle> particles;
public:
    void setRelativePositionInDomain(const std::array<int, 3> &relativePositionInDomain);

private:
    void calculateBoundaries();
    /**
     * @brief position of left back side corner
     */
    std::array<double, 3> position;

    int cellType = INNER_CELL;

public:
    const std::array<double, 3> &getPosition() const;
    std::vector<Cell *> &getNeighbourCells();
    static int getInnerCellValue();
    static int getBoundaryCellValue();
    static int getHaloCellValue();
    int getCellType() const;
    std::vector<Particle> &getParticles();
    void addCellToNeighbours(Cell *pCell);
    bool particleLiesInCell(Particle &p);

    /**
     * Tests if cell is equal to another, based on position
     * @param other
     * @return whether cells are equal
     */
    bool operator==(Cell &other);

    void reflectXtoRightCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint);
    void reflectXtoLeftCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint);
    void reflectYtoTopCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint);
    void reflectYtoBottomCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint);
    void reflectZtoFrontCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint);
    void reflectZtoBackCell(const std::array<double, 3>& pointWhichShouldBeReflected, std::array<double, 3>& resultPoint);
};
#endif //PSEMOLDYN_GROUPG_CELL_H
