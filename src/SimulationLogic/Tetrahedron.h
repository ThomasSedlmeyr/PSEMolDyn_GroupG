//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_TETRAEDA_H
#define PSEMOLDYN_GROUPG_TETRAEDA_H

#include "Body.h"
#include "Tetrahedron.h"

/**
 * This tetrahedron consists of four equilateral triangles of equal size
 */
class Tetrahedron: public Body {
    Tetrahedron(int ID, double meshWidth, double massPerParticle);

    double edgeLength;
    int numberParticlesPerEdge;

public:
    ~Tetrahedron();
protected:
    void parseStructure(const std::string& line) override;
    void generateParticles(int startID);

};


#endif //PSEMOLDYN_GROUPG_TETRAEDA_H
