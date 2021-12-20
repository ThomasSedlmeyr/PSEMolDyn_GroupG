#include <iostream>
#include <list>
#include "input.h"
#include "GeometricObjects/Cuboid.h"
#include "GeometricObjects/Tetrahedron.h"
#include "GeometricObjects/Sphere.h"
#include "XMLParser.h"

double XMLParser::t_end_p;
double XMLParser::delta_t_p;
int XMLParser::calcType_p = 2;
std::string XMLParser::baseNameOutputFiles_p{};
int XMLParser::writeFrequency_p;
std::string XMLParser::gravInput_p{};
double XMLParser::epsilon_p;
double XMLParser::mass_p;
double XMLParser::rho_p;
double XMLParser::h_p;
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
std::list<Body*> XMLParser::bodies_p{};
int XMLParser::particleContainerType;


bool XMLParser::parseXML(const std::string filename) {
    try {
        std::unique_ptr<input> input_xml(input_(filename));

        // parameters parsing
        t_end_p = input_xml->t_end();
        delta_t_p = input_xml->delta_t();
        calcType_p = [](calcType x) {if (x == calcType::G) return 1; else return 2;} (input_xml->calcType());
        baseNameOutputFiles_p = input_xml->baseNameOutputFiles();
        writeFrequency_p = input_xml->writeFrequency();
        gravInput_p = input_xml->gravInput();

        epsilon_p = input_xml->paramsLJ().epsilon();
        mass_p = input_xml->paramsLJ().mass();
        rho_p = input_xml->paramsLJ().rho();
        h_p = input_xml->paramsLJ().h();
        params_p.emplace_back("epsilon", epsilon_p);
        params_p.emplace_back("mass", mass_p);
        params_p.emplace_back("rho", rho_p);
        params_p.emplace_back("h", h_p);
        domainSize[0] = input_xml->paramsLJ().domainSizeX();
        domainSize[1] = input_xml->paramsLJ().domainSizeY();
        domainSize[2] = input_xml->paramsLJ().domainSizeZ();
        particleContainerType = input_xml->paramsLJ().particleContainerType();
        cutoffRadius = input_xml->paramsLJ().cutoffRadius();

        top_p = input_xml->boundaryConditions().top();
        right_p = input_xml->boundaryConditions().right();
        bottom_p = input_xml->boundaryConditions().bottom();
        left_p = input_xml->boundaryConditions().left();
        front_p = input_xml->boundaryConditions().front();
        back_p = input_xml->boundaryConditions().back();

        boundaryConditions = {front_p, right_p, back_p, left_p, top_p, bottom_p};

        // bodies_p parsing with iteration
        particlesLJ::body_sequence &b(input_xml->particlesLJ().body());

        Body* temp = nullptr;
        int id = 1;
        int particleCounter = 0;

        for (particlesLJ::body_iterator i(b.begin()); i != b.end(); ++i) {
            if (i->bodyType() == "Cuboid") {
                temp =  new Cuboid(id, h_p, mass_p);
            } else if (i->bodyType() == "Tetrahedron") {
                temp =  new Tetrahedron(id, h_p, mass_p);
            } else if (i->bodyType() == "Sphere") {
                temp =  new Sphere(id, h_p, mass_p);
            } else {
                std::cout << "Parsing of XML-file was not successful!" << std::endl;
                std::cout << "Unknown body type." << std::endl;
                return false;
            }

            temp->parsePosition(i->position());
            temp->parseInitialV(i->velocity());
            temp->parseStructure(i->objectSpecificFormat());

            temp->generateParticles(particleCounter);
            particleCounter += temp->getParticles().size();

            bodies_p.push_back(temp);
            id++;

            /*
            body->parseStructure(line);
            body->generateParticles(numberParticles);

            numberParticles += body->getParticles().size();
            bodies.push_back(body);
            bodiesCounter++;
             */
        }

    } catch (const std::exception& e) {
        std::cout << "Parsing of XML-file was not successful!" << std::endl;
        std::cout << "Please check that correct path was provided." << std::endl;
        std::cout << "Please check that file was correctly formatted." << std::endl;
        std::cerr << e.what() << std::endl;
        return false;
    }

    // print for testing purposes
    /*
    std::cout << t_end_p << std::endl;
    std::cout << delta_t_p << std::endl;
    std::cout << calcType_p << std::endl;
    std::cout << baseNameOutputFiles_p << std::endl;
    std::cout << writeFrequency_p << std::endl;
    std::cout << gravInput_p << std::endl;
    std::cout << epsilon_p << std::endl;
    std::cout << mass_p << std::endl;
    std::cout << rho_p << std::endl;
    std::cout << h_p << std::endl;
    std::cout << top_p << std::endl;
    std::cout << right_p << std::endl;
    std::cout << bottom_p << std::endl;
    std::cout << left_p << std::endl;
    std::cout << front_p << std::endl;
    std::cout << back_p << std::endl;
    */
    return true;
}

void XMLParser::resetInternalData() {
    params_p.clear();
    bodies_p.clear();
    domainSize = {};
    boundaryConditions = {};
}
