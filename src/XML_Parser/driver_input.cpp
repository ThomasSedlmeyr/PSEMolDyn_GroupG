#include <iostream>
#include <list>
#include "input.h"
#include "GeometricObjects/Cuboid.h"
#include "GeometricObjects/Tetrahedron.h"
#include "GeometricObjects/Sphere.h"
#include "driver_input.h"

double driver_input::t_end_p;
double driver_input::delta_t_p;
int driver_input::calcType_p;
std::string driver_input::baseNameOutputFiles_p;
int driver_input::writeFrequency_p;
std::string driver_input::gravInput_p;

double driver_input::epsilon_p;
double driver_input::mass_p;
double driver_input::rho_p;
double driver_input::h_p;
std::vector<std::tuple<std::string, double>> driver_input::params_p;

int driver_input::top_p;
int driver_input::right_p;
int driver_input::bottom_p;
int driver_input::left_p;
int driver_input::front_p;
int driver_input::back_p;

std::list<Body*> driver_input::bodies_p;

bool driver_input::parseXML(const std::string filename) {
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

        top_p = input_xml->boundaryConditions().top();
        right_p = input_xml->boundaryConditions().right();
        bottom_p = input_xml->boundaryConditions().bottom();
        left_p = input_xml->boundaryConditions().left();
        front_p = input_xml->boundaryConditions().front();
        back_p = input_xml->boundaryConditions().back();

        // bodies_p parsing with iteration
        particlesLJ::body_sequence &b(input_xml->particlesLJ().body());

        Body* temp = nullptr;
        int id = 1;

        for (particlesLJ::body_iterator i(b.begin()); i != b.end(); ++i) {
            if (i->bodyType().compare("Cuboid")) {
                temp =  new Cuboid(id, h_p, mass_p);
            } else if (i->bodyType().compare("Tetrahedron")) {
                temp =  new Tetrahedron(id, h_p, mass_p);
            } else if (i->bodyType().compare("Sphere")) {
                temp =  new Sphere(id, h_p, mass_p);
            } else {
                std::cout << "Parsing of XML-file was not successful!" << std::endl;
                std::cout << "Unknown body type." << std::endl;
                return false;
            }

            temp->parsePosition(i->position());
            temp->parseInitialV(i->velocity());
            temp->parseStructure(i->objectSpecificFormat());

            /*
             * necessary when parsing particles?
            temp->generateParticles(numberParticles);
            numberParticles += body->getParticles().size();
            */

            bodies_p.push_back(temp);
            id++;
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // print for testing purposes

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

    return true;
}