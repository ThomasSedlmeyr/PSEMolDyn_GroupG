#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <GeometricObjects/Cuboid.h>
#include <chrono>
#include <ParticleContainers/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "OutputWriter/XYZWriter.h"
#include "OutputWriter/VTKWriter.h"
#include "XML_Parser/XMLParser.h"
#include "BoundaryConditions//ReflectingCondition.h"
#include "utils/ArrayUtils.h"
#include "2D/ParticleContainerLinkedCells2D.h"

//Code adapted from
//https://stackoverflow.com/questions/28768359/comparison-of-floating-point-arrays-using-google-test-and-google-mock
#define EXPECT_DOUBLE_NEARLY_EQ(expected, actual, thresh) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;\
        }

/**
 * @brief When the PeriodicBoundaryCondition is used every Cell should have 26 neighbour cells.
 */
TEST(BoundaryConditions, TestNumberOfNeighbourCellsForPeriodicCondition) {
    double cutOff = 3.0;
    double domainSizeX = 20;
    double domainSizeY = 30;
    double domainSizeZ = 40;

    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(domainSizeX, domainSizeY, domainSizeZ, cutOff, fours);
    std::array<double, 3> domainSize = {domainSizeX, domainSizeY, domainSizeZ};
    auto boundaryConditionContainer = std::make_unique<BoundaryConditionContainer>(fours,
                                                                                   ParticleContainerLinkedCells::numberCellsX,
                                                                                   ParticleContainerLinkedCells::numberCellsY,
                                                                                   ParticleContainerLinkedCells::numberCellsZ,
                                                                                   domainSize);

    std::array<BoundaryCondition *, 6> boundaryConditions = boundaryConditionContainer->getBoundaryConditions();

    for (auto cell: ParticleContainerLinkedCells::boundaryCells) {
        EXPECT_EQ(cell->getNeighbourCells().size(), 26);
    }
}

/**
 * @brief Tests for every side of the boundary of the reflection and inserting of particle in the halo cells works as expected
 */
TEST(BoundaryConditions, TestReflectionAndInserting) {
    double cutOff = 3.0;
    double domainSizeX = 20;
    double domainSizeY = 30;
    double domainSizeZ = 40;

    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(domainSizeX, domainSizeY, domainSizeZ, cutOff, fours);
    std::array<double, 3> domainSize = {domainSizeX, domainSizeY, domainSizeZ};
    auto boundaryConditionContainer = std::make_unique<BoundaryConditionContainer>(fours,
                                                                                   ParticleContainerLinkedCells::numberCellsX,
                                                                                   ParticleContainerLinkedCells::numberCellsY,
                                                                                   ParticleContainerLinkedCells::numberCellsZ,
                                                                                   domainSize);
    std::array<BoundaryCondition *, 6> boundaryConditions = boundaryConditionContainer->getBoundaryConditions();

    Particle particleLeft = Particle({-1, 1, 1}, {1, 2, 3}, 23, 1, 1);
    Particle particleRight = Particle({domainSizeX + 1, 2, 2}, {1, 2, 3}, 23, 1, 2);
    Particle particleTop = Particle({1, domainSizeY + 1, 1}, {1, 2, 3}, 23, 1, 3);
    Particle particleBottom = Particle({1, -1, 1}, {1, 2, 3}, 23, 1, 4);
    Particle particleFront = Particle({1, 1, domainSizeZ + 1}, {1, 2, 3}, 23, 1, 5);
    Particle particleBack = Particle({1, 1, -1}, {1, 2, 3}, 23, 1, 6);
    //Edge cases
    Particle particleLeftBottomFront = Particle({-1, -2, domainSizeZ + 1.5}, {1, 2, 3}, 23, 1, 7);

    ParticleContainerLinkedCells::addParticle(particleLeft);
    ParticleContainerLinkedCells::addParticle(particleRight);
    ParticleContainerLinkedCells::addParticle(particleTop);
    ParticleContainerLinkedCells::addParticle(particleBottom);
    ParticleContainerLinkedCells::addParticle(particleFront);
    ParticleContainerLinkedCells::addParticle(particleBack);
    ParticleContainerLinkedCells::addParticle(particleLeftBottomFront);
    ParticleContainerLinkedCells::addParticle(particleLeftBottomFront);

    boundaryConditionContainer->calculateBoundaryConditions();
    boundaryConditionContainer->doWorkAfterCalculationStep();
    std::vector<Particle> particles = particleContainer.getParticles();

    std::sort(std::begin(particles),
              std::end(particles),
              [](const Particle &p1, const Particle &p2) { return p1.getId() < p2.getId(); });

    std::array<double, 3> expectedPositionLeftParticle{19, 1, 1};
    EXPECT_DOUBLE_NEARLY_EQ(expectedPositionLeftParticle, particles[0].getX(), 0.00000001);
    expectedPositionLeftParticle = {1, 2, 2};
    EXPECT_DOUBLE_NEARLY_EQ(expectedPositionLeftParticle, particles[1].getX(), 0.00000001);
    expectedPositionLeftParticle = {1, 1, 1};
    EXPECT_DOUBLE_NEARLY_EQ(expectedPositionLeftParticle, particles[2].getX(), 0.00000001);
    expectedPositionLeftParticle = {1, domainSizeY - 1, 1};
    EXPECT_DOUBLE_NEARLY_EQ(expectedPositionLeftParticle, particles[3].getX(), 0.00000001);
    expectedPositionLeftParticle = {1, 1, 1};
    EXPECT_DOUBLE_NEARLY_EQ(expectedPositionLeftParticle, particles[4].getX(), 0.00000001);
    expectedPositionLeftParticle = {1, 1, domainSizeZ - 1};
    EXPECT_DOUBLE_NEARLY_EQ(expectedPositionLeftParticle, particles[5].getX(), 0.00000001);
    expectedPositionLeftParticle = {domainSizeX - 1, domainSizeY - 2, 1.5};
    EXPECT_DOUBLE_NEARLY_EQ(expectedPositionLeftParticle, particles[6].getX(), 0.00000001);
}

/**
 * We place in in two corners of the domain and on an edge one particle and check if get 17 get ghostParticles
 * and also checks the correct deletion of the ghost particles
 */
TEST(BoundaryConditions, CheckBoundarTestNumberGhostParticles) {
    double cutOff = 2.0;
    double domainSizeX = 10;
    double domainSizeY = 12;
    double domainSizeZ = 14;

    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(domainSizeX, domainSizeY, domainSizeZ, cutOff, fours);
    std::array<double, 3> domainSize = {domainSizeX, domainSizeY, domainSizeZ};
    auto boundaryConditionContainer = std::make_unique<BoundaryConditionContainer>(fours,
                                                                                   ParticleContainerLinkedCells::numberCellsX,
                                                                                   ParticleContainerLinkedCells::numberCellsY,
                                                                                   ParticleContainerLinkedCells::numberCellsZ,
                                                                                   domainSize);
    std::array<BoundaryCondition *, 6> boundaryConditions = boundaryConditionContainer->getBoundaryConditions();

    Particle particleLeft = Particle({1, 1, 3}, {1, 2, 3}, 23, 1, 1);
    Particle particleLeftBottomFront = Particle({1, 1, domainSizeZ - 1}, {1, 2, 3}, 23, 1, 1);
    Particle particleRightTopBack = Particle({domainSizeX - 1, domainSizeY - 1, 1}, {1, 2, 3}, 23, 1, 2);

    ParticleContainerLinkedCells::addParticle(particleLeft);
    ParticleContainerLinkedCells::addParticle(particleRightTopBack);
    ParticleContainerLinkedCells::addParticle(particleLeftBottomFront);

    boundaryConditionContainer->calculateBoundaryConditions();
    std::vector<Particle> particles = particleContainer.getParticles();

    std::vector<Particle> ghostParticles = {};
    std::copy_if(particles.begin(), particles.end(),
                 std::back_inserter(ghostParticles),
                 [](const Particle &p) { return p.getId() == Particle::GHOST_TYPE; });
    EXPECT_EQ(17, ghostParticles.size());

    boundaryConditionContainer->doWorkAfterCalculationStep();
    particles.clear();
    ghostParticles.clear();
    particles = particleContainer.getParticles();
    std::copy_if(particles.begin(), particles.end(),
                 std::back_inserter(ghostParticles),
                 [](const Particle &p) { return p.getId() == Particle::GHOST_TYPE; });
    EXPECT_EQ(0, ghostParticles.size());
    EXPECT_EQ(3, particles.size());
}

bool checkIfArrayIsElementInOtherVector(std::array<double, 3> &array, std::vector<std::array<double, 3>> otherVector) {
    for (auto &arr: otherVector) {
        bool arrayIsContained = true;
        for (int i = 0; i < arr.size(); i++) {
            if (abs(arr[i] - array[i]) > 0.0000001) {
                arrayIsContained = false;
                break;
            }
        }
        if (arrayIsContained) {
            return true;
        }
    }
    return false;
}


TEST(BoundaryConditions, CheckPositionsOfGhostParticles3D) {
    double cutOff = 2.0;
    double domainSizeX = 10;
    double domainSizeY = 12;
    double domainSizeZ = 14;

    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(domainSizeX, domainSizeY, domainSizeZ, cutOff, fours);
    std::array<double, 3> domainSize = {domainSizeX, domainSizeY, domainSizeZ};
    auto boundaryConditionContainer = std::make_unique<BoundaryConditionContainer>(fours,
                                                                                   ParticleContainerLinkedCells::numberCellsX,
                                                                                   ParticleContainerLinkedCells::numberCellsY,
                                                                                   ParticleContainerLinkedCells::numberCellsZ,
                                                                                   domainSize);
    std::array<BoundaryCondition *, 6> boundaryConditions = boundaryConditionContainer->getBoundaryConditions();

    Particle particleLeftTopEdge = Particle({1, 1, 3}, {1, 2, 3}, 23, 1, 1);
    Particle particleLeftBottomFront = Particle({1, 1, domainSizeZ - 1}, {1, 2, 3}, 23, 1, 1);
    Particle particleRightTopBack = Particle({domainSizeX - 1, domainSizeY - 1, 1}, {1, 2, 3}, 23, 1, 2);

    ParticleContainerLinkedCells::addParticle(particleLeftTopEdge);
    ParticleContainerLinkedCells::addParticle(particleLeftBottomFront);
    ParticleContainerLinkedCells::addParticle(particleRightTopBack);


    boundaryConditionContainer->calculateBoundaryConditions();
    std::vector<Particle> particles = particleContainer.getParticles();

    std::vector<Particle> ghostParticles = {};
    std::copy_if(particles.begin(), particles.end(),
                 std::back_inserter(ghostParticles),
                 [](const Particle &p) { return p.getId() == Particle::GHOST_TYPE; });

    std::vector<std::array<double, 3>> ghostParticlePoints(ghostParticles.size());
    for (int i = 0; i < ghostParticles.size(); i++) {
        ghostParticlePoints[i] = ghostParticles[i].getX();
    }
    std::array<std::array<double, 3>, 17> referencePoints{{
                                                                  //position for ghost particles for particleLeftTopEdge
                                                                  {1 + domainSizeX, 1, 3},
                                                                  {1, 1 + domainSizeY, 3},
                                                                  {1 + domainSizeX, domainSizeY + 1,
                                                                   3}, //Left particle{}

                                                                  //positions for ghost particles leftBottomFront
                                                                  {1 + domainSizeX, 1, domainSizeZ - 1}, //we go right
                                                                  {1 + domainSizeX, 1, -1}, //we go right and back
                                                                  {1 + domainSizeX, 1 + domainSizeY,
                                                                   domainSizeZ - 1}, //we go right up and back
                                                                  {1 + domainSizeX, 1 + domainSizeY,
                                                                   -1},//we go right up
                                                                  {1, 1 + domainSizeY, -1}, // we go up go back
                                                                  {1, 1 + domainSizeY, domainSizeZ - 1}, //we go up
                                                                  {1, 1, -1} //we go back

                                                                  //positions for ghost particles for rightTopBack
                                                                  //{domainSizeX - 1, domainSizeY - 1, 1}
                                                                  ,
                                                                  {-1, domainSizeY - 1, 1}, //we go left
                                                                  {-1, -1, 1}, //we go left and down
                                                                  {-1, domainSizeY - 1,
                                                                   domainSizeZ + 1}, //we go left and front
                                                                  {-1, -1,
                                                                   domainSizeZ + 1}, //we go left, down and front
                                                                  {domainSizeX - 1, -1, 1}, //we go down
                                                                  {domainSizeX - 1, domainSizeY - 1,
                                                                   domainSizeZ + 1}, //we go front
                                                                  {domainSizeX - 1, -1,
                                                                   domainSizeZ + 1}, //we go down and front/**/
                                                          }};


    for (auto &referencePoint: referencePoints) {
        if (!checkIfArrayIsElementInOtherVector(referencePoint, ghostParticlePoints)) {
            std::cout << "Point: (" << referencePoint[0] << "," << referencePoint[1] << "," << referencePoint[2] << ")"
                      << std::endl;
            EXPECT_EQ(true, false);
        }
    }
}

/*
TEST(BoundaryConditions, CheckPositionsOfGhostParticles2D) {
    double cutOff = 2.0;
    double domainSizeX = 10;
    double domainSizeY = 12;

    std::array<int, 4> fours = {4, 4, 4, 4};
    twoD::ParticleContainerLinkedCells2D particleContainer(domainSizeX, domainSizeY, cutOff, fours);
    std::array<double, 3> domainSize = {domainSizeX, domainSizeY};
    auto boundaryConditionContainer = std::make_unique<twoD::BoundaryConditionContainer2D>(fours,
                                                                                   ParticleContainerLinkedCells::numberCellsX,
                                                                                   ParticleContainerLinkedCells::numberCellsY,
                                                                                   domainSize);
    std::array<twoD::BoundaryCondition2D *, 4> boundaryConditions = boundaryConditionContainer->getBoundaryConditions();

    Particle particleLeft = Particle({1, 1, 0}, {1, 2, 0}, 23, 1, 1);
    //Particle particleLeftBottomFront = Particle({1, 1, domainSizeZ - 1}, {1, 2, 3}, 23, 1, 1);
    //Particle particleRightTopBack = Particle({domainSizeX - 1, domainSizeY - 1, 1}, {1, 2, 3}, 23, 1, 2);

    ParticleContainerLinkedCells::addParticle(particleLeft);
    //ParticleContainerLinkedCells::addParticle(particleRightTopBack);
    //ParticleContainerLinkedCells::addParticle(particleLeftBottomFront);

    boundaryConditionContainer->calculateBoundaryConditions();
    std::vector<Particle> particles = particleContainer.getParticles();

    std::vector<Particle> ghostParticles = {};
    std::copy_if(particles.begin(), particles.end(),
                 std::back_inserter(ghostParticles),
                 [](const Particle &p) { return p.getId() == Particle::GHOST_TYPE; });

    std::vector<std::array<double, 3>> ghostParticlePoints(ghostParticles.size());
    for(int i = 0; i <ghostParticles.size(); i++){
        ghostParticlePoints[i] = ghostParticles[i].getX();
    }

    std::array<std::array<double, 3>, 3>  referencePoints{{{1+domainSizeX,1,0}, {1,1+domainSizeY,0}, {1+domainSizeX,1+domainSizeY,0}}};
    for(auto& referencePoint : referencePoints){
        EXPECT_EQ(true, checkIfArrayIsElementInOtherVector(referencePoint, ghostParticlePoints));
    }
}*/
