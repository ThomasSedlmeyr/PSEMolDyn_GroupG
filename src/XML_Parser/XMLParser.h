#ifndef PSEMOLDYN_GROUPG_XMLPARSER_H
#define PSEMOLDYN_GROUPG_XMLPARSER_H

#include <iostream>
#include <list>
#include "input.h"
#include "GeometricObjects/Cuboid.h"
#include "GeometricObjects/Tetrahedron.h"
#include "GeometricObjects/Sphere.h"

class XMLParser {
public:
    /**
     * @brief parsed end time from xml file
     */
    static double t_end_p;

    /**
     * @brief parsed stepsize from xml file
     */
    static double delta_t_p;

    /**
     * @brief parsed calculation type from xml file (1=gravitationSimulation, 2=lennardJonesSimulation)
     */
    static int calcType_p;

    /**
     * @brief parsed base name for output files from xml file
     */
    static std::string baseNameOutputFiles_p;

    /**
     * @brief parsed write frequency from xml file
     */
    static int writeFrequency_p;

    /**
     * @brief parsed path to input file fot gravitation simulation from xml file
     */
    static std::string gravInput_p;

    /**
     * @brief parsed parameter epsilon from xml file
     */
    static double epsilon_p;

    /**
     * @brief parsed parameter mass from xml file
     */
    static double mass_p;

    /**
     * @brief parsed parameter rho from xml file
     */
    static double rho_p;

    /**
     * @brief parsed parameter for mesh width distance from xml file
     */
    static double h_p;

    /**
     * @brief vector for handling parameters
     */
    static std::vector<std::tuple<std::string, double>> params_p;

    /**
     * @brief parsed boundary condition for top side from xml file
     */
    static int top_p;

    /**
     * @brief parsed boundary condition for right side from xml file
     */
    static int right_p;

    /**
     * @brief parsed boundary condition for bottom side from xml file
     */
    static int bottom_p;

    /**
     * @brief parsed boundary condition for left side from xml file
     */
    static int left_p;

    /**
     * @brief parsed boundary condition for front side from xml file
     */
    static int front_p;

    /**
     * @brief parsed boundary condition for back side from xml file
     */
    static int back_p;

    /**
     * @brief vector for handling boundary conditions
     */
    static std::array<int, 6> boundaryConditions;

    /**
     * @brief list of parsed bodies from xml file
     */
    static std::list<Body*> bodies_p;

    /**
     * @brief parsed particle container type from xml file (1=directSum, 2=linkedCells
     */
    static int particleContainerType;

    /**
     * @brief array of parsed domain sizes from xml file
     */
    static std::array<double, 3> domainSize;

    /**
     * @brief parsed cutoff radius from xml file
     */
    static double cutoffRadius;

    /**
     * @brief function for parsing xml input file
     * @return true if parsing successful, false otherwise
     */
    static bool parseXML(const std::string);
};

#endif //PSEMOLDYN_GROUPG_XMLPARSER_H