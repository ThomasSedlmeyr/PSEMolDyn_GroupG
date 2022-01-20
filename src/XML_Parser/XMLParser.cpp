#include <iostream>
#include <list>
#include "input.h"
#include "GeometricObjects/Cuboid.h"
#include "GeometricObjects/Tetrahedron.h"
#include "GeometricObjects/Sphere.h"
#include "XMLParser.h"
#include "BodyBuilder.h"
#include "SimulationLogic/Thermostat.h"
#include "SimulationLogic/Simulation.h"

double XMLParser::t_end_p;
double XMLParser::delta_t_p;
int XMLParser::calcType_p = 2;
std::string XMLParser::baseNameOutputFiles_p{};
int XMLParser::writeFrequency_p;
std::string XMLParser::gravInput_p{};
std::vector<std::tuple<std::string, double>> XMLParser::params_p{};
int XMLParser::top_p;
int XMLParser::right_p;
int XMLParser::bottom_p;
int XMLParser::left_p;
int XMLParser::front_p;
int XMLParser::back_p;
std::array<double, 3> XMLParser::domainSize = {};
double XMLParser::cutoffRadius;
std::array<int, 6> XMLParser::boundaryConditions;
particlesLJ::body_sequence XMLParser::bodySequence{};
int XMLParser::particleContainerType_p;
double XMLParser::g_grav_p;
bool XMLParser::useGravity_p;
bool XMLParser::loadCheckpoint_p;
bool XMLParser::makeCheckpoint_p;
std::string XMLParser::pathInCheckpoint_p{};
std::string XMLParser::pathOutCheckpoint_p{};
bool XMLParser::useThermostat_p;
double XMLParser::T_init_p = -1;
double XMLParser::T_target_p = -1;
double XMLParser::delta_T_p;
int XMLParser::n_thermostat_p;
int XMLParser::dimensionType_p;
bool XMLParser::useBrownianMotion_p;
int XMLParser::parallelType_p;
int XMLParser::thermostatType_p;
int XMLParser::gravDirection_p;
bool XMLParser::useVelDensProfiling_p;
int XMLParser::numberOfBins_p;

bool XMLParser::parseXML(const std::string filename) {
    try {
        std::unique_ptr<input> input_xml(input_(filename));

        t_end_p = input_xml->generalParams().t_end();
        delta_t_p = input_xml->generalParams().delta_t();
        writeFrequency_p = input_xml->generalParams().writeFrequency();
        dimensionType_p = [](dimensionType x) {if (x == dimensionType::cxx_2D) return 2; else return 3;} (input_xml->generalParams().dimensionType());
        switch (input_xml->generalParams().parallelType()) {
            case parallelType::notParallel:
                parallelType_p = Simulation::NOTPARALLEL;
                break;
            case parallelType::first:
                parallelType_p = Simulation::FIRSTPARALLEL;
                break;
            case parallelType::second:
                parallelType_p = Simulation::SECONDPARALLEL;
                break;
            default:
                parallelType_p = Simulation::NOTPARALLEL;
        }

        g_grav_p = input_xml->generalParams().g_grav();
        useGravity_p = [](yesNo x) {if (x == yesNo::yes) return true; else return false;} (input_xml->generalParams().useGravity());
        if (input_xml->generalParams().gravDirection() == gravDirectionType::z) {
            gravDirection_p = 2;
        } else if (input_xml->generalParams().gravDirection() == gravDirectionType::y) {
            gravDirection_p = 1;
        } else {
            gravDirection_p = 0;
        }

        calcType_p = [](calcType x) {if (x == calcType::G) return 1; else return 2;} (input_xml->generalParams().calcType());
        baseNameOutputFiles_p = input_xml->generalParams().baseNameOutputFiles();
        particleContainerType_p = [](particleContainerType x) {if (x == particleContainerType::directSum) return 1; else return 2;} (input_xml->generalParams().particleContainerType());
        cutoffRadius = input_xml->generalParams().cutoffRadius();
        gravInput_p = input_xml->generalParams().gravInput();

        loadCheckpoint_p = [](yesNo x) {if (x == yesNo::yes) return true; else return false;} (input_xml->generalParams().loadCheckpoint());
        makeCheckpoint_p = [](yesNo x) {if (x == yesNo::yes) return true; else return false;} (input_xml->generalParams().makeCheckpoint());
        pathInCheckpoint_p = input_xml->generalParams().pathInCheckpoint();
        pathOutCheckpoint_p = input_xml->generalParams().pathOutCheckpoint();

        domainSize[0] = input_xml->generalParams().domainSizeX();
        domainSize[1] = input_xml->generalParams().domainSizeY();
        domainSize[2] = input_xml->generalParams().domainSizeZ();

        useThermostat_p = [](yesNo x) {if (x == yesNo::yes) return true; else return false;} (input_xml->generalParams().useThermostat());
        thermostatType_p = [](thermostatType x) {if (x == thermostatType::regular) return Thermostat::REGULAR; else return Thermostat::ONLYFLUID;} (input_xml->generalParams().thermostatType());
        useBrownianMotion_p = [](yesNo x) {if (x == yesNo::yes) return true; else return false;} (input_xml->generalParams().useBrownianMotion());
        T_init_p = input_xml->generalParams().T_init();
        T_target_p = input_xml->generalParams().T_target();
        delta_T_p = input_xml->generalParams().delta_T();
        n_thermostat_p = input_xml->generalParams().n_thermostat();

        useVelDensProfiling_p = input_xml->generalParams().useVelDensProfiling();
        numberOfBins_p = input_xml->generalParams().numberOfBins();

        if (input_xml->boundaryConditions().top() == "outflowType") {
            top_p = 1;
        } else if (input_xml->boundaryConditions().top() == "reflectingType") {
            top_p = 2;
        } else if (input_xml->boundaryConditions().top() == "betterReflectingType") {
            top_p = 3;
        } else {
            top_p = 4;
        }
        if (input_xml->boundaryConditions().right() == "outflowType") {
            right_p = 1;
        } else if (input_xml->boundaryConditions().right() == "reflectingType") {
            right_p = 2;
        } else if (input_xml->boundaryConditions().right() == "betterReflectingType") {
            right_p = 3;
        } else {
            right_p = 4;
        }
        if (input_xml->boundaryConditions().bottom() == "outflowType") {
            bottom_p = 1;
        } else if (input_xml->boundaryConditions().bottom() == "reflectingType") {
            bottom_p = 2;
        } else if (input_xml->boundaryConditions().bottom() == "betterReflectingType") {
            bottom_p = 3;
        } else {
            bottom_p = 4;
        }
        if (input_xml->boundaryConditions().left() == "outflowType") {
            left_p = 1;
        } else if (input_xml->boundaryConditions().left() == "reflectingType") {
            left_p = 2;
        } else if (input_xml->boundaryConditions().left() == "betterReflectingType") {
            left_p = 3;
        } else {
            left_p = 4;
        }
        if (input_xml->boundaryConditions().front() == "outflowType") {
            front_p = 1;
        } else if (input_xml->boundaryConditions().front() == "reflectingType") {
            front_p = 2;
        } else if (input_xml->boundaryConditions().front() == "betterReflectingType") {
            front_p = 3;
        } else {
            front_p = 4;
        }
        if (input_xml->boundaryConditions().back() == "outflowType") {
            back_p = 1;
        } else if (input_xml->boundaryConditions().back() == "reflectingType") {
            back_p = 2;
        } else if (input_xml->boundaryConditions().back() == "betterReflectingType") {
            back_p = 3;
        } else {
            back_p = 4;
        }
        boundaryConditions = {front_p, right_p, back_p, left_p, top_p, bottom_p};
        bodySequence = input_xml->particlesLJ().body();
        return true;

    } catch (const std::exception& e) {
        std::cout << "Parsing of XML-file was not successful!" << std::endl;
        std::cout << "Please check that correct path was provided." << std::endl;
        std::cout << "Please check that file was correctly formatted." << std::endl;
        std::cerr << e.what() << std::endl;
        return false;
    }
}

void XMLParser::resetInternalData() {
    params_p.clear();
    domainSize = {};
    boundaryConditions = {};
}
