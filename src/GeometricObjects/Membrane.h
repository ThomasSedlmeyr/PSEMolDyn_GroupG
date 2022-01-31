//
// Created by thomas on 29.12.21.
//

#ifndef PSEMOLDYN_GROUPG_MEMBRANE_H
#define PSEMOLDYN_GROUPG_MEMBRANE_H


#include <array>
#include <string>
#include "Body.h"

extern double rZero;
extern double k;
extern int t_lift_end;

class Membrane : public Body {
private:
    /**
     * @brief the dimensions of the membran. In Z-direction should be one
     */
    std::array<double, 3> dimensions{};

    /**
     * @brief the x- and y-Positions of the particles at which f is applied
     */
    std::vector<std::array<int, 2>> positionsWhereFisApplied;

    /**
     * @brief calculates with positionsWhereFisApplied the particles on which f should be applied
     */
    void setParticlesWhereFisApplied();

public:
    Membrane(int ID, double meshWidth, double massPerParticle);
    ~Membrane() override;

    void parseStructure(const std::string& line) override;
    void generateParticles(int startID) override;

    /**
     * TODO Kommentar muss Philip schreiben
     */
    void setNeighbourParticles();
};

#endif //PSEMOLDYN_GROUPG_MEMBRANE_H
