#include <iostream>
#include <list>
#include "input.h"
#include "../GeometricObjects/Cuboid.h"
#include "../GeometricObjects/Tetrahedron.h"
#include "../GeometricObjects/Sphere.h"
#include "driver_input.h"

using namespace std;

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
                cout << "Parsing of XML-file was not successful!" << endl;
                cout << "Unknown body type." << endl;
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
        std::cerr << e.what() << endl;
    }

    // print for testing purposes

    cout << t_end_p << endl;
    cout << delta_t_p << endl;
    cout << calcType_p << endl;
    cout << baseNameOutputFiles_p << endl;
    cout << writeFrequency_p << endl;
    cout << gravInput_p << endl;
    cout << epsilon_p << endl;
    cout << mass_p << endl;
    cout << rho_p << endl;
    cout << h_p << endl;
    cout << top_p << endl;
    cout << right_p << endl;
    cout << bottom_p << endl;
    cout << left_p << endl;
    cout << front_p << endl;
    cout << back_p << endl;

    return true;
}