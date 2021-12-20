//
// Created by thomas on 05.11.21.
//

#ifndef PSEMOLDYN_GROUPG_CUBOID_H
#define PSEMOLDYN_GROUPG_CUBOID_H
#include "array"
#include "SimulationLogic/Particle.h"
#include <string>
#include <vector>

class Body {

protected:
    /**
     * @brief Initial velocity of the body
     */
    std::array<double, 3> initialV;

    /**
     * @brief the initial position of the body
     */
    std::array<double, 3> position;

    /**
     *@brief the particles which were created by the Body
     */
    std::vector<Particle> particles;

    /**
     *@brief the mesh width of the particles in the body
     */
    double meshWidth;

    /**
     * @ the mass of every particle in the body
     */
    double massPerParticle;

    /**
     * @brief this ID is unique for every body
     */
    int ID;

    /**
     * @brief This function is able to parse three with comma separated double values
     * @param line The string containing the with comma seperated double values
     * @return the resulting double array
     */
    std::array<double, 3> parseLineWithThreeValues(const std::string &line);

    /**
     * @brief This value specifies the epsilon for all particles in the body
     */
    double epsilon;

    /**
     * @brief This value specifies the rho for all particles in the body
     */
    double rho;

public:
    /**
     *@brief getter for initiaö velocity
     */
    const std::array<double, 3> &getInitialV() const;

    /**
     *@brief getter for mesh width
     */
    double getMeshWidth() const;

    Body(int ID, double meshWidth, double massPerParticle);

    /**
     * @brief returns the particles of the body
     * @return vector of particles of body
     */
    std::vector<Particle> &getParticles();

    /**
     * @brief  parse the initialV for one Line
     * @param line the line in the file which contains the comma seperated values
     */
    void parseInitialV(const std::string& line);

    /**
     * @brief  parse the initial position for one Line
     * @param line the line in the file which contains the comma seperated values
     */
    void parsePosition(const std::string& line);

    /**
     * @brief parses the body specific structure
     * @param line the line which contains the comma seperated values
     */
    virtual void parseStructure(const std::string& line) = 0;

    /**
     * @brief generates all particles which are in the body
     * @param startID the startId with which the first particle is initialized
     */
    virtual void generateParticles(int startID) = 0;
};


#endif //PSEMOLDYN_GROUPG_CUBOID_H
