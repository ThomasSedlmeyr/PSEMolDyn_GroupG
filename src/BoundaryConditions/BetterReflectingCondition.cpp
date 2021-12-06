//
// Created by thomas on 30.11.21.
//

#include "BetterReflectingCondition.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"

void BetterReflectingCondition::calculateBoundaryConditionForCell(Cell *cell) {
    switch (side) {
        case FRONT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                std::array<double, 3> reflectedPoint{};
                Particle particle = cell->getParticles()[i];
                cell->reflectZtoBackCell(particle.getX(), reflectedPoint);
                particle.setX(reflectedPoint);
                //inverting the velocity component
                particle.getVRef()[2] *= -1;
                ParticleContainerLinkedCells::addParticle(particle);
            }
            break;
        case BACK:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                std::array<double, 3> reflectedPoint{};
                Particle particle = cell->getParticles()[i];
                cell->reflectZtoFrontCell(particle.getX(), reflectedPoint);
                particle.setX(reflectedPoint);
                //inverting the velocity component
                particle.getVRef()[2] *= -1;
                ParticleContainerLinkedCells::addParticle(particle);
            }
            break;
        case RIGHT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                std::array<double, 3> reflectedPoint{};
                Particle particle = cell->getParticles()[i];
                cell->reflectXtoLeftCell(particle.getX(), reflectedPoint);
                particle.setX(reflectedPoint);
                //inverting the velocity component
                particle.getVRef()[0] *= -1;
                ParticleContainerLinkedCells::addParticle(particle);
            }
            break;
        case LEFT:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                std::array<double, 3> reflectedPoint{};
                Particle particle = cell->getParticles()[i];
                cell->reflectXtoRightCell(particle.getX(), reflectedPoint);
                particle.setX(reflectedPoint);
                //inverting the velocity component
                particle.getVRef()[0] *= -1;
                ParticleContainerLinkedCells::addParticle(particle);
            }
            break;
        case TOP:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                std::array<double, 3> reflectedPoint{};
                Particle particle = cell->getParticles()[i];
                cell->reflectYtoBottomCell(particle.getX(), reflectedPoint);
                particle.setX(reflectedPoint);
                //inverting the velocity component
                particle.getVRef()[1] *= -1;
                ParticleContainerLinkedCells::addParticle(particle);
            }
            break;
        case BOTTOM:
            for (int i = 0; i < cell->getParticles().size(); ++i) {
                std::array<double, 3> reflectedPoint{};
                Particle particle = cell->getParticles()[i];
                cell->reflectYtoTopCell(particle.getX(), reflectedPoint);
                particle.setX(reflectedPoint);
                //inverting the velocity component
                particle.getVRef()[1] *= -1;
                ParticleContainerLinkedCells::addParticle(particle);
            }
            break;
    }
    //Delete all particles
    cell->getParticles().clear();
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

