//
// Created by thomas on 05.11.21.
//

#include "Cuboid.h"
Cuboid :: Cuboid(int id){
    ID = id;
}





void Cuboid::parseStructure(const std::string &line) {
    dimensions = parseLineWithThreeValues(line);
}

void Cuboid::generateParticles() {
    particles = std::vector<Particle>(dimensions[0] * dimensions[1] * dimensions[2]);
    //Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
    //        double m_arg, int type_arg
    std::array<double, 3> newPosition;
    for (int i = 0; i < dimensions[0]; ++i) {
        for (int j = 0; j < dimensions[1]; ++j) {
            for (int k = 0; k < dimensions[2]; ++k) {
                newPosition = position;
                newPosition[0] += meshWidth * i;
                newPosition[1] += meshWidth * j;
                newPosition[2] += meshWidth * k;
                particles.emplace_back(newPosition, initialV, massPerParticle, ID);
            }
        }
    }
    numberParticles = particles.size();
}

void Cuboid::setStructure(const std::array<double, 3> &dim){
    Cuboid::dimensions = dim;
}

Cuboid::~Cuboid() {

}


