#ifndef PSEMOLDYN_GROUPG_CELL_H
#define PSEMOLDYN_GROUPG_CELL_H


#include <vector>
#include <memory>
#include "Particle.h"

class Cell {

public:
    /**
     * @brief This type stands for the innerCells
     */
    static const int INNER_CELL = 0;

    /**
     * @brief This type stands for the BoundaryCells
     */
    static const int BOUNDARY_CELL = 1;

    /**
     * @brief This  type stands for the haloCells
     */
    static const int HALO_CELL = 2;

    /**
     * all cells have the same size in xDirection which is determined by the cutOffRadius
     */
    static double sizeX;

    /**
     * all cells have the same size in yDirection which is determined by the cutOffRadius
     */
    static double sizeY;

    /**
     * all cells have the same size in zDirection which is determined by the cutOffRadius
     */
    static double sizeZ;

    /**
     * @brief the right boundary of the cell
     */
    double xBoundary{};
    /**
     *@brief the top boundary of the cell
     */
    double yBoundary{};
    /**
     * @brief the front boundary of the cell
     */
    double zBoundary{};

    Cell(std::vector<Particle> particles, const std::array<double, 3> &position, int cellType);

    Cell(std::vector<Particle> particles, const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType);

    Cell(const std::array<double, 3> &position, int cellType);

    Cell(const std::array<double, 3> &position, std::array<int, 3> relativePositionInDomain, int cellType);

    Cell();

    [[nodiscard]] const std::array<int, 3> &getRelativePositionInDomain() const;

    /**
     * @brief sets the relative position of the cell to the other cells in the domain
     * @param relativePositionInDomain
     */
    void setRelativePositionInDomain(const std::array<int, 3> &relativePositionInDomain);

    [[nodiscard]] const std::array<double, 3> &getPosition() const;

    std::vector<Cell *> &getNeighbourCells();

    [[nodiscard]] int getCellType() const;

    std::vector<Particle> &getParticles();

    /**
     * @brief get the constant innerCellType. This methode is need because the test can
     * not access the static constant variables
     * @return the type
     */
    static const int getInnerCellType();

    /**
     * @brief get the constant boundaryCellType. This methode is need because the test can
     * not access the static constant variables
     * @return the type
     */
    static const int getBoundaryCellType();

    /**
     * @brief get the constant haloCellType. This methode is need because the test can
     * not access the static constant variables
     * @return the type
     */
    static const int getHaloCellType();

    /**
     * @brief Adds a pointer of a Cell to the vector storing the neighbour cells
     * @param pCell the pointer which should be added
     */
    void addCellToNeighbours(Cell *pCell);

    /**
     * @brief Evaluates if the position of a certain particle lies in this specific cell
     * @param p the particle which position is evaluated
     * @return whether the the position of p is located in the cell
     */
    bool particleLiesInCell(Particle &p);

    /**
     * @brief Tests if cell is equal to another, based on position
     * @param other
     * @return whether cells are equal
     */
    bool operator==(Cell &other);

    /**
     * @brief Reflects a specific point to the right neighbourCell by changing only the x-Coordinate
     * @param pointWhichShouldBeReflected the point which should be reflected
     * @param resultPoint the result of the reflected point will be stored here
     */
    void
    reflectXtoRightCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint);

    /**
     * @brief Reflects a specific point to the left neighbourCell by changing only the x-Coordinate
     * @param pointWhichShouldBeReflected the point which should be reflected
     * @param resultPoint the result of the reflected point will be stored here
     */
    void
    reflectXtoLeftCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint);

    /**
     * @brief Reflects a specific point to the top neighbourCell by changing only the y-Coordinate
     * @param pointWhichShouldBeReflected the point which should be reflected
     * @param resultPoint the result of the reflected point will be stored here
     */
    void
    reflectYtoTopCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint);

    /**
     * @brief Reflects a specific point to the bottom neighbourCell by changing only the y-Coordinate
     * @param pointWhichShouldBeReflected the point which should be reflected
     * @param resultPoint the result of the reflected point will be stored here
     */
    void
    reflectYtoBottomCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint);

    /**
     * @brief Reflects a specific point to the front neighbourCell by changing only the z-Coordinate
     * @param pointWhichShouldBeReflected the point which should be reflected
     * @param resultPoint the result of the reflected point will be stored here
     */
    void
    reflectZtoFrontCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint);

    /**
     * @brief Reflects a specific point to the back neighbourCell by changing only the z-Coordinate
     * @param pointWhichShouldBeReflected the point which should be reflected
     * @param resultPoint the result of the reflected point will be stored here
     */
    void
    reflectZtoBackCell(const std::array<double, 3> &pointWhichShouldBeReflected, std::array<double, 3> &resultPoint);

    /**
     * @brief Deletes all particles which were stored in the cell
     */
    void clearParticles();

private:
    /**
     * @brief the relative position of the cell in the domain
     */
    std::array<int, 3> relativePositionInDomain{};

    /**
     * contains a pointer to every neighbour cell
     */
    std::vector<Cell *> neighbourCells;

    /**
     * particles contained in the cell
     */
    std::vector<Particle> particles;

    /**
     * @brief sets the x-, y- and z-Boundary of the cells
     */
    void calculateBoundaries();

    /**
     * @brief position of left back side corner
     */
    std::array<double, 3> position{};

    int cellType = INNER_CELL;

};
#endif //PSEMOLDYN_GROUPG_CELL_H
