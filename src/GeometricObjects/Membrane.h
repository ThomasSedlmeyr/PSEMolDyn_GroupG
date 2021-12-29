//
// Created by thomas on 29.12.21.
//

#ifndef PSEMOLDYN_GROUPG_MEMBRANE_H
#define PSEMOLDYN_GROUPG_MEMBRANE_H


#include <array>
#include <string>
#include "Body.h"

class Membrane : public Body {
private:
    //TODO: This values have to be parsed in parseStructure from the XML-File
    /**
     * @brief the dimensions of the membran. In Z-direction should be one
     */
    std::array<double, 3> dimensions{};

    /**
     * @brief the average bond length of the molecule
     */
    double rZero;

    /**
     * @brief the stiffness constant
     */
    double k;

    /**
     * @brief the force which is applied in z-direction to certain particles of the membrane
     */
    double fZup;

    /**
     * @brief the number of time steps for which f is Applied to certain particles of the domain
     */
    int numberTimeStepsForWhichFisApplied;

    /**
     * @brief the x- and y-Positions of the particles at which f is applied
     */
    std::vector<std::array<int, 2>> positionsWhereFisApplied;

    /**
     * @brief a vector of pointers pointing on the particles on which f should be applied
     */
    std::vector<Particle*> particlesWhereFisApplied;

    /**
     * @brief applies the harmonic potential to all particles of the membrane
     */
    void applyTheHarmonicPotential();

    /**
     * @brief calculates with positionsWhereFisApplied the particles on which f should be applied
     */
    //void setParticlesWhereFisApplied();


public:
    Membrane(int ID, double meshWidth, double massPerParticle);
    ~Membrane() override;

    void parseStructure(const std::string& line) override;
    void generateParticles(int startID) override;


    };

#endif //PSEMOLDYN_GROUPG_MEMBRANE_H
