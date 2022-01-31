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

    /**
     * The length of every edge of the tetrahedron
     */
    double edgeLength;

    /**
     * The number of particles with which the edge
     */
    int numberParticlesPerEdge;

public:
    Tetrahedron(int ID, double meshWidth, double massPerParticle, bool movingIsAllowed);
    ~Tetrahedron();

protected:
    void parseStructure(const std::string& line) override;
    void generateParticles(int startID) override;

};


#endif //PSEMOLDYN_GROUPG_TETRAEDA_H
