//
// Created by thomas on 24.11.21.
//

#ifndef PSEMOLDYN_GROUPG_PARTICLECONTAINERLINKEDCELLS_H
#define PSEMOLDYN_GROUPG_PARTICLECONTAINERLINKEDCELLS_H


#include <vector>
#include <memory>
#include "Cell.h"
#include "ParticleContainer.h"
#include "BoundaryConditionContainer.h"

class ParticleContainerLinkedCells : public ParticleContainer{
    /**
     * @brief all cells of the domain inner-, boundary-, halo-cells
     */
private:
    std::unique_ptr<BoundaryConditionContainer> boundaryContainer;
    static std::vector<Cell> cells;
    int currentIndexInCells{};
    int currentIndexHaloCells{};
    int currentIndexBoundaryCells{};
    int currentIndexInnerCells{};

    double domainSizeX{};
    double domainSizeY{};
    double domainSizeZ{};

    double cutOffRadius{};

    std::array<double, 3> currentPosition{};

    /**
     * The left front side Corner of the domain the haloCells are excluded
     * in the most common cases this position is (0,0,0)
     */
    std::array<double, 3> domainStartPosition{};

    void buildOneRowInXdirection(int numberStonesInXdirection, int cellType);

    void setDimensionsOfCellPointerVectors();

    void addSingleHaloCell();

    void buildHaloSlice();

    void buildHaloAndBoundarySlice();

    void buildStandardLine();

    void addSingleBoundaryCell();

    void buildStandardSlice();

    void buildFullLineHaloCells();

    void buildLineOneHaloMultipleBoundariesOneHalo();

    /**
     * @brief Determines the indices of the neighbour cells
     * @param index Index of cell for which the neighbours should be returned
     * @return Vector of indices of neighbour cells
     */
    static std::array<int, 26> getNeighbourIndices(int index);

    /**
     * @brief Calculates the index of the cell located a certain distance in x direction from the given cell
     * @param index Index of cell
     * @param numberOfPositions Number of positions to move in x direction
     * @return New index of cell
     */
    static int movePositionsInX(int index, int numberOfPositions);

    /**
     * @brief Calculates the index of the cell located a certain distance in y direction from the given cell
     * @param index Index of cell
     * @param numberOfPositions Number of positions to move in y direction
     * @return New index of cell
     */
    static int movePositionsInY(int index, int numberPositionsInY);

    /**
     * @brief Calculates the index of the cell located a certain distance in z direction from the given cell
     * @param index Index of cell
     * @param numberOfPositions Number of positions to move in z direction
     * @return New index of cell
     */
    static int movePositionsInZ(int index, int numberPositionsInZ);

public:
    static std::vector<Cell*> boundaryCells;
    static std::vector<Cell*> haloCells;
    static std::vector<Cell*> innerCells;
    static int numberCellsX;
    static int numberCellsY;
    static int numberCellsZ;

    static const std::vector<Cell> &getCells() ;

    static const std::vector<Cell *> &getBoundaryCells() ;

    static const std::vector<Cell *> &getHaloCells() ;

    static const std::vector<Cell *> &getInnerCells() ;

    std::vector<Particle> & getParticles() override;

public:
    ParticleContainerLinkedCells();
    ParticleContainerLinkedCells(double domainSizeX, double domainSizeY, double domainSizeZ, double cutOffRadius,
                                  const std::array<double, 3> &domainStartPosition = std::array<double, 3>{0.0, 0.0, 0.0});

    void createCells();
    static void cellsToXYZ();

    /**
     * @brief Iterates over all cells and fills their neighbour vector
     */
    static void setNeighbourCells();

    void addParticleToContainer(Particle &p) override;
    static void addGhostParticle(const std::array<double, 3> &position, double m);
    void updateParticlePositions(ParticleVisitor &visitor) override;
    void walkOverParticles(ParticleVisitor &visitor) override;
    void walkOverParticlePairs(ParticlePairVisitor &visitor) override;

    /**
     * @brief Returns the cell a given particle belongs to
     * @param p Particle
     * @return Cell the particle belongs to
     */
    static int getCellIndexForParticle(const Particle &p);

    static void setRelativeDomainPositionsInCells();

    int getNumberOfParticles();
};


#endif //PSEMOLDYN_GROUPG_PARTICLECONTAINERLINKEDCELLS_H
