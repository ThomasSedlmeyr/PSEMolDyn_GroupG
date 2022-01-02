//
// Created by thomas on 07.11.21.
//

#include "Tetrahedron.h"
#include "utils/ArrayUtils.h"
#include <math.h>

Tetrahedron::~Tetrahedron() {}

void Tetrahedron::parseStructure(const std::string &line) {
    numberParticlesPerEdge = std::stoi(line);
}

void Tetrahedron::generateParticles(int startID) {
    edgeLength = numberParticlesPerEdge *  meshWidth;
    //x right
    //y up and down
    //z behind
    std::array<double, 3> vectorX = {meshWidth,0.0,0.0};
    std::array<double, 3> vectorXZ = {meshWidth*0.5,0.0,sqrt(3)*0.5*meshWidth};
    std::array<double, 3> vectorXYZ = {meshWidth*0.5,meshWidth * sqrt(6) / 3, sqrt(3)*meshWidth/6};
    std::array<double, 3> currentPosition{};

    for (int i = 0; i < numberParticlesPerEdge; i++) {
        for (int j = 0; j < numberParticlesPerEdge-i; j++) {
            for (int k = 0; k < numberParticlesPerEdge-i-j; k++) {
                currentPosition = position + k * vectorX + j * vectorXZ + i * vectorXYZ;
                particles.emplace_back(currentPosition, initialV, massPerParticle, ID, startID, movingIsAllowed);
                startID++;
            }
        }
    }
    numberParticlesPerEdge = particles.size();
}

Tetrahedron::Tetrahedron(int ID, double meshWidth, double massPerParticle, bool movingIsAllowed) : Body(ID, meshWidth, massPerParticle, movingIsAllowed) {

}

