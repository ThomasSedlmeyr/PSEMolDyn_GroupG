#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <SimulationLogic/Cuboid.h>
#include <chrono>
#include <SimulationLogic/ParticleContainerLinkedCells.h>
#include "SimulationLogic/Cell.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

#define EXPECT_FLOATS_NEARLY_EQ(expected, actual, thresh) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;\
        }


TEST(Tests, ReflectionAnglConditionTest) {
    auto ljS = LennardJonesSimulation();
    std::array<int, 6> threes = {3, 3, 3, 3, 3, 3};
    //TODO warum darf ich hier nicht {5,5,5} einstellen???
    ParticleContainerLinkedCells particleContainer(5, 5, 5, 3, threes);
    std::array<double, 3> fives = {5, 5, 5};
    std::unique_ptr<BoundaryConditionContainer> boundaryContainer = std::make_unique<BoundaryConditionContainer>(threes,
                                                                                                                 ParticleContainerLinkedCells::boundaryCells,
                                                                                                                 ParticleContainerLinkedCells::haloCells,
                                                                                                                 ParticleContainerLinkedCells::numberCellsX,
                                                                                                                 ParticleContainerLinkedCells::numberCellsY,
                                                                                                                 ParticleContainerLinkedCells::numberCellsZ,
                                                                                                                 fives);
    //In left halo cell
    Particle p1 = Particle({-1.23, 0, 0}, {-10, 2, 1}, 1, -1, 0);
    particleContainer.addParticleToContainer(p1);
    //In right halo cell
    Particle p2 = Particle({6, 0, 0}, {4, 2, 1}, 1, -1, 1);
    particleContainer.addParticleToContainer(p2);
    //In top halo cell
    Particle p3 = Particle({3, 7, 0}, {-10, 2, 1}, 1, -1, 2);
    particleContainer.addParticleToContainer(p3);
    //In bottom halo cell
    Particle p4 = Particle({0, -1, 0}, {-10, 2, 1}, 1, -1, 3);
    particleContainer.addParticleToContainer(p4);
    //In front halo cell
    Particle p5 = Particle({3, 0, 6}, {-10, 2, 1}, 1, -1, 4);
    particleContainer.addParticleToContainer(p5);
    //In back halo cell
    Particle p6 = Particle({-1.23, 0, -1.5}, {-10, 2, 1}, 1, -1, 5);
    particleContainer.addParticleToContainer(p6);
    //Edge Case:
    //In left and front halo cell
    Particle p7 = Particle({-1.5, 6, 0}, {-10, 2, 1}, 1, -1, 6);
    particleContainer.addParticleToContainer(p7);

    std::vector<Particle> particles = particleContainer.getParticles();
    sort(particles.begin(), particles.end(), [](const Particle &p1, const Particle &p2) {
        return p1.getId() < p2.getId();
    });

    boundaryContainer->calculateBoundaryConditions();
    std::array<std::array<double, 3>, 7> correctPositions = {
            {{1.23, 0, 0}, {4, 0, 0}, {3, 3, 0}, {0, 1, 0}, {3, 0, 4}, {-1.23, 0, 1.5}, {1.5, 4, 0}}};

    for (int i = 0; i < 7; i++) {
        EXPECT_FLOATS_NEARLY_EQ(correctPositions[i], particleContainer.getParticles()[i].getX(), 0.0000001);
    }


}

