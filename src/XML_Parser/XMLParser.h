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
     * @brief body sequence used for parsing bodies
     */
    static particlesLJ::body_sequence bodySequence;

    /**
     * @brief list of parsed bodies from xml file
     */
    static std::list<Body*> bodies_p;

    /**
     * @brief parsed particle container type from xml file (1=directSum, 2=linkedCells
     */
    static int particleContainerType_p;

    /**
     * @brief array of parsed domain sizes from xml file
     */
    static std::array<double, 3> domainSize;

    /**
     * @brief parsed cutoff radius from xml file
     */
    static double cutoffRadius;

    /**
     * @brief value of desired gravity force from xml file
     */
    static double g_grav_p;

    /**
     * @brief whether gravity force should be considered in simulation from xml file
     */
    static bool useGravity_p;

    /**
     * @brief whether checkpoints should be loaded
     */
    static bool loadCheckpoint_p;

    /**
     * @brief whether checkpoints should be made after simulation
     */
    static bool makeCheckpoint_p;

    /**
     * @brief potential path for reading checkpoints
     */
    static std::string pathInCheckpoint_p;

    /**
     * @brief potential path for writing checkpoints
     */
    static std::string pathOutCheckpoint_p;

    /**
     * @brief whether thermostat should be used in simulation
     */
    static bool useThermostat_p;

    /**
     * @brief value of initial temperature from xml file
     */
    static double T_init_p;

    /**
     * @brief value of target temperature from xml file
     */
    static double T_target_p;

    /**
     * @brief value of temperature stepsize from xml file
     */
    static double delta_T_p;

    /**
     * @brief number of time steps for application of thermostat from xml file
     */
    static int n_thermostat_p;

    /**
     * @brief number of dimension for simulation from xml file
     */
    static int dimensionType_p;

    /**
     * @brief function for parsing xml input file
     * @return true if parsing successful, false otherwise
     */
    static bool parseXML(const std::string);

    /**
     * @brief resets static data of XML parser
     */
    static void resetInternalData();
};

#endif //PSEMOLDYN_GROUPG_XMLPARSER_H