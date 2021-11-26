#ifndef PSEMOLDYN_GROUPG_SPHERE_H
#define PSEMOLDYN_GROUPG_SPHERE_H

#include "Body.h"

class Sphere : public Body {

protected:
    void parseStructure(const std::string &line) override;

    void generateParticles(int startID) override;

public:
    Sphere(int ID, double meshWidth, double massPerParticle);

    ~Sphere();

private:
    int numberParticlesPerRadius;
};


#endif //PSEMOLDYN_GROUPG_SPHERE_H
