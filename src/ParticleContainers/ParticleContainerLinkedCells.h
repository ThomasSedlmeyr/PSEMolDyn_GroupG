//
// Created by thomas on 24.11.21.
//

#ifndef PSEMOLDYN_GROUPG_PARTICLECONTAINERLINKEDCELLS_H
#define PSEMOLDYN_GROUPG_PARTICLECONTAINERLINKEDCELLS_H


#include <vector>
#include <memory>
#include <Visitors/UpwardForceVisitor.h>
#include "SimulationLogic/Cell.h"
#include "ParticleContainer.h"
#include "BoundaryConditions/BoundaryConditionContainer.h"
#include "XML_Parser/XMLParser.h"
#include "SimulationLogic/SubdomainContainer.h"

class ParticleContainerLinkedCells : public ParticleContainer {
private:
    /**
     * @brief the BoundaryConditionContainer which is used to calculate the boundary conditions for each domain side
     */
    std::unique_ptr<BoundaryConditionContainer> boundaryContainer;
    /**
     * @brief a global index for the currentIndex of the cell
     */
    int currentIndexInCells{};

    /**
     * @brief a global index for the currentIndex of the haloCells
     */
    int currentIndexHaloCells{};

    /**
     * @brief a global index for the currentIndex of the boundaryCells
     */
    int currentIndexBoundaryCells{};

    /**
     * @brief a global index for the currentIndex of the innerCells
     */
    int currentIndexInnerCells{};


    /**
     * @brief the cutOffRadius. Only particles that are located at a smaller distance around the particle as the cutOffRadius
     * are used for the force calculation.
     */
    double cutOffRadius{};

    /**
     * @brief determines whether gravitation should be applied or not
     */
    const bool useGrav = XMLParser::useGravity_p;

    /**
     * @brief downward gravitation factor
     */
    const double g_grav = XMLParser::g_grav_p;


    static double middleOfDomainInX;
    static double middleOfDomainInY;
    static double middleOfDomainInZ;

    /**
     * @brief in this variable we can globally store a certain position.
     */
    std::array<double, 3> currentPosition{};

    UpwardForceVisitor zGravVisitor{};

    SubdomainContainer subdomainContainer;

    /**
     * @brief builds one row of cells with the same type
     * @param numberCellsInXdirection length of the row which should be built
     * @param cellType the type of the cells with which the row will be built
     */
    void buildOneRowInXdirection(int numberCellsInXdirection, int cellType);

    /**
     * @brief calculates the number of boundary-, halo- and innerCells an resizes their specific vectors
     */
    void setDimensionsOfCellPointerVectors();

    /**
     * @brief inserts a new HaloCells into the cells vector at the position currentIndexAtCells
     */
    void addSingleHaloCell();

    /**
     * @brief builds a whole slice containing only halo cells
     */
    void buildHaloSlice();

    /**
     * @brief builds a slice were the boundary consists only of haloCells an all other cells are only boundaryCells
     */
    void buildHaloAndBoundarySlice();

    /**
     * @brief builds a line  were the boundary consisting only of halo and boundary cells and all other cells are innerCells
     */
    void buildStandardLine();

    /**
     * @brief adds one boundary cell into the cells vector at the position currentIndexAtCells
     */
    void addSingleBoundaryCell();

    /**
     * @brief builds a slice were the boundary consisting only of halo and boundary cells and all other cells are innerCells
     */
    void buildStandardSlice();

    /**
     * @brief build a row containing only haloCells
     */
    void buildFullLineHaloCells();

    /**
     * @brief build a row starting with one haloCell and multiple boundaryCells and ending with one haloCell
     */
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
    /**
     * @brief all cells of the domain
     */
    static std::vector<Cell> cells;

    /**
     * @brief a vector of pointers pointing to all boundaryCells of the domain
     */
    static std::vector<Cell *> boundaryCells;

    /**
     * @brief a vector of pointers pointing to all haloCells of the domain
     */
    static std::vector<Cell *> haloCells;

    /**
     * @brie a vector of pointers pointing to all innerCells of the domain
     */
    static std::vector<Cell *> innerCells;

    /**
     * @brief the number of Cells in X-direction
     */
    static int numberCellsX;

    /**
     * @brief the number of Cells in Y-direction
     */
    static int numberCellsY;

    /**
     * @brief the number of Cells in Z-direction
     */
    static int numberCellsZ;

    /**
 * @brief the x-dimension of the domain
 */
    static double domainSizeX;

    /**
     * @brief the y-dimension of the domain
     */
    static double domainSizeY;

    /**
     * @brief the z-dimension of the domain
     */
    static double domainSizeZ;

    static const std::vector<Cell> &getCells();

    static const std::vector<Cell *> &getBoundaryCells();

    static const std::vector<Cell *> &getHaloCells();

    static const std::vector<Cell *> &getInnerCells();

    std::vector<Particle> &getParticles() override;

    ParticleContainerLinkedCells();

    /**
     * @brief The constructor for ParticleContainerLinkedCells
     *
     * @param domainSizeX the size in x-direction
     * @param domainSizeY the size in y-direction
     * @param domainSizeZ the size in z-direction
     * @param cutOffRadius the cutOffRadius
     * @param boundaryConditionTypes an array containing the boundary condition types in the following order:
     * front, right, back, left, top, bottom
     */
    ParticleContainerLinkedCells(double domainSizeX, double domainSizeY, double domainSizeZ, double cutOffRadius,
                                 const std::array<int, 6> &boundaryConditionTypes = std::array<int, 6>{
                                         BoundaryCondition::REFLECTING_TYPE,
                                         BoundaryCondition::REFLECTING_TYPE,
                                         BoundaryCondition::REFLECTING_TYPE,
                                         BoundaryCondition::REFLECTING_TYPE,
                                         BoundaryCondition::REFLECTING_TYPE,
                                         BoundaryCondition::REFLECTING_TYPE});

    /**
     * @brief builds all the cells which were used for the LinkedCell-Algorithm
     */
    void createCells();

    /**
     * @brief creates a VTK-file which contains a point for every cell. This method is very
     * helpful for debugging.
     */
    static void cellsToVTK();

    /**
     * @brief Iterates over all cells and fills their neighbour vector
     */
    static void setNeighbourCells();

    void addParticleToContainer(Particle &p) override;

    static void addGhostParticle(const std::array<double, 3> &position, const double m, const int type);

    void updateParticlePositions(ParticleVisitor &visitor) override;

    void walkOverParticles(ParticleVisitor &visitor) override;

    void walkOverParticlePairs(ParticlePairVisitor &visitor) override;

    void applyFZUp() override;

    /**
     * @brief Returns the cell a given particle belongs to
     * @param p Particle
     * @return Cell the particle belongs to
     */
    static int getCellIndexForParticle(const Particle &p);

    /**
     * @brief set the relative position of every cell in the domain
     */
    static void setRelativeDomainPositionsInCells();

    /**
     * @brief inserts a specific particle into the right cell
     * @param particle the particle which should be insert into the domain
     */
    static void addParticle(Particle &particle);

    static void reflectPositionInY(std::array<double, 3> &position);

    static void reflectPositionInZ(std::array<double, 3> &position);

    static void reflectPositionInX(std::array<double, 3> &position);

    static void
    add9CellsAtRelativePositionsToNeighboursOfCell(const std::array<std::array<int, 3>, 9> &relativePositions,
                                                   const std::array<double, 3> &positionOfCell);

    void walkOverParticlePairs2(ParticlePairVisitor &visitor);
};


#endif //PSEMOLDYN_GROUPG_PARTICLECONTAINERLINKEDCELLS_H
