//
// Created by thomas on 30.11.21.
//

#include "BetterReflectingCondition.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

void BetterReflectingCondition::calculateBoundaryConditionForCell(Cell *cell) {
    switch (side) {
        case FRONT:
            for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                Particle particle = cell->getParticles()[i];
                if (!particle.isGhostParticle){
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectZtoBackCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[2] *= -1;
                    ParticleContainerLinkedCells::addParticle(particle);
                    cell->getParticles().erase(cell->getParticles().begin() + i);
                    i--;
                }
            }
            break;
        case BACK:
            for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                Particle particle = cell->getParticles()[i];
                if (!particle.isGhostParticle) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectZtoFrontCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[2] *= -1;
                    ParticleContainerLinkedCells::addParticle(particle);
                    cell->getParticles().erase(cell->getParticles().begin() + i);
                    i--;
                }
            }
            break;
        case RIGHT:
            for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                Particle particle = cell->getParticles()[i];
                if (!particle.isGhostParticle) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectXtoLeftCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[0] *= -1;
                    ParticleContainerLinkedCells::addParticle(particle);
                    cell->getParticles().erase(cell->getParticles().begin() + i);
                    i--;
                }
            }
            break;
        case LEFT:
            for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                Particle particle = cell->getParticles()[i];
                if (!particle.isGhostParticle) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectXtoRightCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[0] *= -1;
                    ParticleContainerLinkedCells::addParticle(particle);
                    cell->getParticles().erase(cell->getParticles().begin() + i);
                    i--;
                }
            }
            break;
        case TOP:
            for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                Particle particle = cell->getParticles()[i];
                if (!particle.isGhostParticle) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectYtoBottomCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[1] *= -1;
                    ParticleContainerLinkedCells::addParticle(particle);
                    cell->getParticles().erase(cell->getParticles().begin() + i);
                    i--;
                }
            }
            break;
        case BOTTOM:
            for (int i = 0; i < static_cast<int>(cell->getParticles().size()); ++i) {
                Particle particle = cell->getParticles()[i];
                if (!particle.isGhostParticle) {
                    std::array<double, 3> reflectedPoint{};
                    cell->reflectYtoTopCell(particle.getX(), reflectedPoint);
                    particle.setX(reflectedPoint);
                    //inverting the velocity component
                    particle.getVRef()[1] *= -1;
                    ParticleContainerLinkedCells::addParticle(particle);
                    cell->getParticles().erase(cell->getParticles().begin() + i);
                    i--;
                }
            }
            break;
    }
}

BetterReflectingCondition::BetterReflectingCondition(int conditionType, int side)
        : BoundaryCondition(conditionType, side) {
}

void BetterReflectingCondition::doWorkAfterCalculationStep() {
}

void BetterReflectingCondition::calculateBoundaryCondition() {
    for (auto &cell: specificHaloCells) {
        calculateBoundaryConditionForCell(cell);
    }
}

