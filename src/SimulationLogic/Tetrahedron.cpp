//
// Created by thomas on 07.11.21.
//

#include "Tetrahedron.h"
#include "utils/ArrayUtils.h"
#include <math.h>
#include <vector>

Tetrahedron::~Tetrahedron() {}


void Tetrahedron::generateParticles(int startID) {
    edgeLength = numberParticlesPerEdge *  meshWidth;
    std::array<double, 3> vectorX = {0.0,meshWidth,0.0};
    std::array<double, 3> vectorXY = {sqrt(3)*0.5*meshWidth,meshWidth*0.5,0.0};
    std::array<double, 3> vectorXYZ = {sqrt(3)*0.25*meshWidth,meshWidth*0.25, meshWidth * sqrt(6) / 3};
    std::array<double, 3> currentPosition;
    std::vector<Particle> particles;
    for (int i = 0; i < numberParticlesPerEdge; ++i) {
        for (int j = 0; j < numberParticlesPerEdge-i; ++j) {
            for (int k = 0; k < numberParticlesPerEdge-i-k; ++j) {
                currentPosition = position + k * vectorX + j * vectorXY + i * vectorXYZ;
                particles.emplace_back(currentPosition, initialV, massPerParticle, ID, startID);
                startID++;
            }
        }
    }
}

void Tetrahedron::parseStructure(const std::string &line) {

}

Tetrahedron::Tetrahedron(int ID, double meshWidth, double massPerParticle) : Body(ID, meshWidth, massPerParticle) {

}

