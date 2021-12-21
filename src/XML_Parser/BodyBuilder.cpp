//
// Created by thomas on 18.12.21.
//

#include <cmath>
#include <iostream>
#include <list>
#include "BodyBuilder.h"
#include "GeometricObjects/Body.h"
#include "GeometricObjects/Cuboid.h"
#include "GeometricObjects/Tetrahedron.h"
#include "GeometricObjects/Sphere.h"

std::vector<std::vector<double>> BodyBuilder::rhoLookUpTable{};
std::vector<std::vector<double>> BodyBuilder::epsilonLookUpTable{};

void BodyBuilder::createLookUpTables(const std::vector<double> &valuesForLookUpRho,
                                     const std::vector<double> &valuesForLookUpEpsilon) {
    //create rho lookup
    rhoLookUpTable.resize(valuesForLookUpRho.size());
    for (int i = 0; i < valuesForLookUpRho.size(); i++) {
        rhoLookUpTable[i] = std::vector<double>(valuesForLookUpRho.size());
        for (int j = 0; j < valuesForLookUpRho.size(); j++) {
            rhoLookUpTable[i][j] = (valuesForLookUpRho[i] + valuesForLookUpRho[j]) / 2;
        }
    }

    //Create epsilon lookup
    epsilonLookUpTable.resize(valuesForLookUpEpsilon.size());
    for (int i = 0; i < valuesForLookUpEpsilon.size(); i++) {
        epsilonLookUpTable[i] = std::vector<double>(valuesForLookUpEpsilon.size());
        for (int j = 0; j < valuesForLookUpEpsilon.size(); j++) {
            epsilonLookUpTable[i][j] = sqrt(valuesForLookUpEpsilon[i] * valuesForLookUpEpsilon[j]);
        }
    }
}


bool BodyBuilder::buildBodies(std::list<Body*>& bodies, particlesLJ::body_sequence& bodySequence){
   Body* body = nullptr;
   int id = 0;
   int particleCounter = 0;
   double mass,  rho,  epsilon,  h;
   std::vector<double> valuesForLookUpRho(bodySequence.size());
   std::vector<double> valuesForLookUpEpsilon(bodySequence.size());

   for (particlesLJ::body_iterator i(bodySequence.begin()); i != bodySequence.end(); ++i) {
       //TODO these values have to be set here mass,  rho,  epsilon,  h;
       valuesForLookUpRho[id] = rho;
       valuesForLookUpEpsilon[id] = epsilon;

       if (i->bodyType() == "Cuboid") {
           body =  new Cuboid(id, h, mass);
       } else if (i->bodyType() == "Tetrahedron") {
           body =  new Tetrahedron(id, h, mass);
       } else if (i->bodyType() == "Sphere") {
           body =  new Sphere(id, h, mass);
       } else {
           std::cout << "Parsing of XML-file was not successful!" << std::endl;
           std::cout << "Unknown body type." << std::endl;
           return false;
       }

       body->parsePosition(i->position());
       body->parseInitialV(i->velocity());
       body->parseStructure(i->objectSpecificFormat());

       body->generateParticles(particleCounter);
       particleCounter += body->getParticles().size();

       bodies.push_back(body);
       id++;
   }
   createLookUpTables(valuesForLookUpRho, valuesForLookUpEpsilon);
}