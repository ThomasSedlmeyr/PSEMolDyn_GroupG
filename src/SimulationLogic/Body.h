//
// Created by thomas on 05.11.21.
//

#ifndef PSEMOLDYN_GROUPG_CUBOID_H
#define PSEMOLDYN_GROUPG_CUBOID_H
#include "array"
#include "Particle.h"
#include <string>
#include <vector>

class Body{
protected:
    /**
     * Position of the particle
     */
    std::array<double, 3> initialV;
    std::array<double, 3> position;

    std::vector<Particle*> particles;

    double meshWidth;
    double massPerParticle;
    int numberOfParticles;

private:
    std::array<double, 3> parseLineWithThreeValues(const std::string& line);

public:
    void parseInitialV(const std::string& line);
    void parsePosition(const std::string& line);
    virtual void parseStructure(const std::string& line) = 0;

    virtual std::vector<Particle> generateParticles() = 0;

    //Die sollten wir eigentlich nicht mehr brauchen
    void setInitialV(const std::array<double, 3> &initialV);
    void setPosition(const std::array<double, 3> &position);
};


#endif //PSEMOLDYN_GROUPG_CUBOID_H
