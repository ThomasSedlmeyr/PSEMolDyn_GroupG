//
// Created by thomas on 18.12.21.
//

#ifndef PSEMOLDYN_GROUPG_BODYBUILDER_H
#define PSEMOLDYN_GROUPG_BODYBUILDER_H


#include <list>
#include <vector>
#include "GeometricObjects/Body.h"
#include "input.h"

class BodyBuilder {
public:
    /**
     * @brief Lookup table for mixed rho values between all bodies
     */
    static std::vector<std::vector<double>> rhoLookUpTable;

    /**
     * @brief Lookup table for mixed epsilon values between all bodies
     */
    static std::vector<std::vector<double>> epsilonLookUpTable;

    /**
     * @brief All singular rho values of the bodies
     */
    static std::vector<double> valuesForLookUpRho;

    /**
     * @brief All singular epsilon values of the bodies
     */
    static std::vector<double> valuesForLookUpEpsilon;

    /**
     * @brief Creates the bodies from the given bodySequence and adds them to the given list of bodies
     * @param bodies
     * @param bodySequence
     * @return whether the method was successful
     */
    static bool buildBodies(std::list<Body*> &bodies, particlesLJ::body_sequence& bodySequence);

    /**
     * @return string representation of the lookup tables and their size
     */
    static std::string toString();

    /**
     * @brief Setup lookup tables according to given size
     * @param s size of the lookup tables as string
     */
    static void parseNumberOfBodies(const std::string& s);

    /**
     * @brief Parse the rho lookup table from given string representation
     * @param lookupTableString
     */
    static void parseRhoLookupTable(const std::string& lookupTableString);

    /**
     * @brief Parse the epsilon lookup table from given string representation
     * @param lookupTableString
     */
    static void parseEpsilonLookupTable(const std::string &lookupTableString);

private:
    /**
     * @brief Calculate the mixed rho/epsilons and store them in corresponding lookup tables
     */
    static void createLookUpTables();
    /**
     * @brief Parse the given string representation of the lookup table into the given actual lookup table
     * @param lookupTable
     * @param lookupTableString
     */
    static void parseSingleLookupTable(std::vector<std::vector<double>> &lookupTable, const std::string &lookupTableString);
};


#endif //PSEMOLDYN_GROUPG_BODYBUILDER_H