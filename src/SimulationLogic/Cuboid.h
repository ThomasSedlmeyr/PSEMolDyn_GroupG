//
// Created by thomas on 05.11.21.
//

#ifndef PSEMOLDYN_GROUPG_RECTANGE_CUBOID_H
#define PSEMOLDYN_GROUPG_RECTANGE_CUBOID_H

#include "array"
#include "Body.h"
#include "Cuboid.h"

class Cuboid: public Body {
private:
    std::array<double, 3> dimensions;

public:
    Cuboid();
    ~Cuboid();

    void parseStructure(const std::string& line) override;
    std::vector<Particle> generateParticles();

    void setStructure(const std::array<double, 3> &dim);
};


#endif //PSEMOLDYN_GROUPG_RECTANGE_CUBOID_H
