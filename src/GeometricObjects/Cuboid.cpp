#include "Cuboid.h"
Cuboid :: Cuboid(int ID, double meshWidth, double massPerParticle, bool isMovingAllowed) : Body(ID, meshWidth, massPerParticle, isMovingAllowed){}


void Cuboid::parseStructure(const std::string &line) {
    dimensions = parseLineWithThreeValues(line);
}

void Cuboid::generateParticles(int startIndex) {
    particles = std::vector<Particle>(dimensions[0] * dimensions[1] * dimensions[2]);
    //Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
    //        double m_arg, int type_arg
    std::array<double, 3> newPosition{};
    int counter = 0;
    for (int i = 0; i < dimensions[0]; ++i) {
        for (int j = 0; j < dimensions[1]; ++j) {
            for (int k = 0; k < dimensions[2]; ++k) {
                newPosition[0] = position[0] + meshWidth * i;
                newPosition[1] = position[1] + meshWidth * j;
                newPosition[2] = position[2] + meshWidth * k;
                particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startIndex, movingIsAllowed);
                particles[counter].isPartOfMembrane = false;
                startIndex++;
                counter++;
            }
        }
    }
}

void Cuboid::setStructure(const std::array<double, 3> &dim){
    Cuboid::dimensions = dim;
}

Cuboid::~Cuboid() = default;


