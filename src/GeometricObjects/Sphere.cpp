#include "Sphere.h"
#include "Cuboid.h"
#include <stdio.h>
#include "utils/ArrayUtils.h"

Sphere::Sphere(int ID, double meshWidth, double massPerParticle) : Body(ID, meshWidth, massPerParticle) {}


void Sphere::parseStructure(const std::string &line) {

}

void Sphere::generateParticles(int startID) {
    //Set the initial number of particles in the sphere
    particles = std::vector<Particle>(numberParticlesPerRadius * numberParticlesPerRadius * numberParticlesPerRadius);

    std::array<double, 3> newPosition{}, leftFrontSideCornerCube{};
    double radiusSize = meshWidth * numberParticlesPerRadius;

    leftFrontSideCornerCube = {position[0] - radiusSize, position[1] - radiusSize, position[2] + radiusSize};
    int counter = 0;
    for (int i = 0; i < numberParticlesPerRadius; ++i) {
        for (int j = 0; j < numberParticlesPerRadius; ++j) {
            for (int k = 0; k < numberParticlesPerRadius; ++k) {
                newPosition[0] = leftFrontSideCornerCube[0] + meshWidth * i;
                newPosition[1] = leftFrontSideCornerCube[1] + meshWidth * j;
                newPosition[2] = leftFrontSideCornerCube[2] + meshWidth * k;

                //If the new position is inside the sphere
                if (ArrayUtils::L2Norm(newPosition - position) <= radiusSize) {
                    particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startID);
                    startID++;
                    counter++;
                }
            }
        }
    }
    particles.resize(counter);
}

void Sphere::generateParticles2d(int startID) {
    //Set the initial size of the particles
    particles = std::vector<Particle>(numberParticlesPerRadius * numberParticlesPerRadius * numberParticlesPerRadius);

    std::array<double, 3> newPosition{}, leftFrontSideCornerCube{};
    double radiusSize = meshWidth * numberParticlesPerRadius;

    leftFrontSideCornerCube = {position[0] - radiusSize, position[1] - radiusSize, position[2] + radiusSize};
    int counter = 0;
    for (int i = 0; i < numberParticlesPerRadius; ++i) {
        for (int j = 0; j < numberParticlesPerRadius; ++j) {
            newPosition[0] = leftFrontSideCornerCube[0] + meshWidth * i;
            newPosition[1] = leftFrontSideCornerCube[1] + meshWidth * j;
            newPosition[2] = 0;

            //If the new position is inside the sphere
            if (ArrayUtils::L2Norm(newPosition - position) <= radiusSize) {
                particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startID);
                startID++;
                counter++;
            }
        }
    }
    particles.resize(counter);
}


