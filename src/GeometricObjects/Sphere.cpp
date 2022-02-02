#include "Sphere.h"
#include "utils/ArrayUtils.h"
#include "XML_Parser/XMLParser.h"

bool Sphere::is2D = true;

Sphere::Sphere(int ID, double meshWidth, double massPerParticle, bool isMovingAllowed) :
    Body(ID, meshWidth, massPerParticle, isMovingAllowed) {
    is2D = XMLParser::dimensionType_p==2;
}

void Sphere::parseStructure(const std::string &line) {
    numberParticlesPerRadius = std::stoi(line);
}

void Sphere::generateParticles(int startID) {
    //Set the initial number of particles in the sphere
    if (is2D) {
        generateParticles2d(startID);
        return;
    }
    particles = std::vector<Particle>(
            8 * numberParticlesPerRadius * numberParticlesPerRadius * numberParticlesPerRadius);

    std::array<double, 3> newPosition{}, leftFrontSideCornerCube{};
    double cuboidSize = (numberParticlesPerRadius - 1) * meshWidth + 0.5 * meshWidth;
    leftFrontSideCornerCube = {position[0] - cuboidSize, position[1] - cuboidSize, position[2] - cuboidSize};
    double radiusSize = numberParticlesPerRadius * meshWidth;

    int counter = 0;
    for (int i = 0; i < numberParticlesPerRadius * 2; ++i) {
        for (int j = 0; j < numberParticlesPerRadius * 2; ++j) {
            for (int k = 0; k < numberParticlesPerRadius * 2; ++k) {
                newPosition[0] = leftFrontSideCornerCube[0] + meshWidth * i;
                newPosition[1] = leftFrontSideCornerCube[1] + meshWidth * j;
                newPosition[2] = leftFrontSideCornerCube[2] + meshWidth * k;

                //If the new position is inside the sphere
                if (ArrayUtils::L2Norm(newPosition - position) <= radiusSize) {
                    particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startID, movingIsAllowed);
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
    particles = std::vector<Particle>(numberParticlesPerRadius * numberParticlesPerRadius * 4);

    std::array<double, 3> newPosition{}, leftFrontSideCornerCube{};
    double cuboidSize = (numberParticlesPerRadius - 1) * meshWidth + 0.5 * meshWidth;
    leftFrontSideCornerCube = {position[0] - cuboidSize, position[1] - cuboidSize, position[2]};
    double radiusSize = numberParticlesPerRadius * meshWidth;

    int counter = 0;
    for (int i = 0; i < numberParticlesPerRadius * 2; ++i) {
        for (int j = 0; j < numberParticlesPerRadius * 2; ++j) {
            newPosition[0] = leftFrontSideCornerCube[0] + meshWidth * i;
            newPosition[1] = leftFrontSideCornerCube[1] + meshWidth * j;
            newPosition[2] = position[2];

            //If the new position is inside the sphere
            if (ArrayUtils::L2Norm(newPosition - position) <= radiusSize) {
                particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startID);
                particles[counter].isPartOfMembrane = false;
                startID++;
                counter++;
            }
        }
    }
    particles.resize(counter);
}

Sphere::~Sphere() = default;


