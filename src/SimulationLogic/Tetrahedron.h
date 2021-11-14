//
// Created by thomas on 07.11.21.
//

#ifndef PSEMOLDYN_GROUPG_TETRAEDA_H
#define PSEMOLDYN_GROUPG_TETRAEDA_H

#include "Body.h"
#include "Tetrahedron.h"

class Tetrahedron: public Body {
    double edgeLength;
    int numberParticlesPerEdge;

public:
    Tetrahedron();
    ~Tetrahedron();
protected:
    void parseStructure(const std::string& line) override;
    void generateParticles();

};


#endif //PSEMOLDYN_GROUPG_TETRAEDA_H
