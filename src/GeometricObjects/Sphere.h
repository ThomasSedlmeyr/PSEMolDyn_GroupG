#ifndef PSEMOLDYN_GROUPG_SPHERE_H
#define PSEMOLDYN_GROUPG_SPHERE_H

#include "Body.h"

class Sphere : public Body {

protected:
    void parseStructure(const std::string &line) override;

    void generateParticles(int startID) override;

public:
    Sphere(int ID, double meshWidth, double massPerParticle, int numberParticlesPerRadius, bool isMovingAllowed = true);

    Sphere(int ID, double meshWidth, double massPerParticle);

    ~Sphere();

    /**
     * @brief specifies if the generated sphere is a disk
     */
    static bool is2D;
private:
    int numberParticlesPerRadius;

    /**
     * Generates a disk which can be used for 2d simulations
     * @param startID the ID of the body
     */
    void generateParticles2d(int startID);
};


#endif //PSEMOLDYN_GROUPG_SPHERE_H
