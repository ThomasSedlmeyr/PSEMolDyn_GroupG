//
// Created by thomas on 30.11.21.
//

#include "BetterReflectingCondition2D.h"
#include "ParticleContainerLinkedCells2D.h"

namespace twoD {
    void BetterReflectingCondition2D::calculateBoundaryConditionForCell(Cell *cell) {
        switch (side) {
            case RIGHT:
                for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                    std::array<double, 3> reflectedPoint{};
                    Particle particle = cell->getParticles()[i];
                    cell->reflectXtoLeftCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[0] *= -1;
                    ParticleContainerLinkedCells2D::addParticle(particle);
                }
                break;
            case LEFT:
                for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                    std::array<double, 3> reflectedPoint{};
                    Particle particle = cell->getParticles()[i];
                    cell->reflectXtoRightCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[0] *= -1;
                    ParticleContainerLinkedCells2D::addParticle(particle);
                }
                break;
            case TOP:
                for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                    std::array<double, 3> reflectedPoint{};
                    Particle particle = cell->getParticles()[i];
                    cell->reflectYtoBottomCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[1] *= -1;
                    ParticleContainerLinkedCells2D::addParticle(particle);
                }
                break;
            case BOTTOM:
                for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                    std::array<double, 3> reflectedPoint{};
                    Particle particle = cell->getParticles()[i];
                    cell->reflectYtoTopCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[1] *= -1;
                    ParticleContainerLinkedCells2D::addParticle(particle);
                }
                break;
        }
        //Delete all particles
        cell->getParticles().clear();
    }

    BetterReflectingCondition2D::BetterReflectingCondition2D(int conditionType, int side)
            : BoundaryCondition2D(conditionType, side) {
    }

    void BetterReflectingCondition2D::doWorkAfterCalculationStep() {
    }

    void BetterReflectingCondition2D::calculateBoundaryCondition() {
        for (auto &cell: specificHaloCells) {
            calculateBoundaryConditionForCell(cell);
        }
    }
}

