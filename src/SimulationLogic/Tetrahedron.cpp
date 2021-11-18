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
    //x Rechts
    //y hoch runter
    //z raus
    std::array<double, 3> vectorX = {meshWidth,0.0,0.0};
    std::array<double, 3> vectorXZ = {meshWidth*0.5,0.0,sqrt(3)*0.5*meshWidth};
    std::array<double, 3> vectorXYZ = {meshWidth*0.5,meshWidth * sqrt(6) / 3, sqrt(3)*meshWidth/6};
    std::array<double, 3> currentPosition;

    int i = 0;
    for (int i = 0; i < numberParticlesPerEdge; i++) {
        for (int j = 0; j < numberParticlesPerEdge-i; j++) {
            for (int k = 0; k < numberParticlesPerEdge-i-j; k++) {
                currentPosition = position + k * vectorX + j * vectorXZ + i * vectorXYZ;
                particles.emplace_back(currentPosition, initialV, massPerParticle, ID, startID);
                startID++;
            }
        }
    }
    numberParticlesPerEdge = particles.size();
}

void Tetrahedron::parseStructure(const std::string &line) {
    numberParticlesPerEdge = std::stoi(line);
}

Tetrahedron::Tetrahedron(int ID, double meshWidth, double massPerParticle) : Body(ID, meshWidth, massPerParticle) {

}

