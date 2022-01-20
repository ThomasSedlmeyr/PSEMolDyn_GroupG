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
#include "Checkpoints/CheckpointReader.h"
#include "GeometricObjects/Membrane.h"

std::vector<std::vector<double>> BodyBuilder::rhoLookUpTable{};
std::vector<std::vector<double>> BodyBuilder::epsilonLookUpTable{};

std::vector<double> BodyBuilder::valuesForLookUpRho{};
std::vector<double> BodyBuilder::valuesForLookUpEpsilon{};

void BodyBuilder::createLookUpTables() {
    //create rho lookup
    rhoLookUpTable.resize(valuesForLookUpRho.size());
    epsilonLookUpTable.resize(valuesForLookUpEpsilon.size());
    //both tables have same size, so one for loop is enough
    for (int i = 0; i < static_cast<int>(valuesForLookUpRho.size()); i++) {
        rhoLookUpTable[i] = std::vector<double>(valuesForLookUpRho.size());
        epsilonLookUpTable[i] = std::vector<double>(valuesForLookUpEpsilon.size());
        for (int j = 0; j < static_cast<int>(valuesForLookUpRho.size()); j++) {
            rhoLookUpTable[i][j] = (valuesForLookUpRho[i] + valuesForLookUpRho[j]) / 2;
            epsilonLookUpTable[i][j] = sqrt(valuesForLookUpEpsilon[i] * valuesForLookUpEpsilon[j]);
        }
    }
}


bool BodyBuilder::buildBodies(std::list<Body*>& bodies, particlesLJ::body_sequence& bodySequence){
    Body* body;
    int id = 0;
    int particleCounter = 0;
    double mass, h;
    bool isMoving;

    int numberOfBodiesReadFromCheckpoint = static_cast<int>(rhoLookUpTable.size());
    //sets the sizes to the total number of bodies in the simulation
    valuesForLookUpRho.resize(numberOfBodiesReadFromCheckpoint +  bodySequence.size());
    valuesForLookUpEpsilon.resize(numberOfBodiesReadFromCheckpoint + bodySequence.size());
    if (XMLParser::loadCheckpoint_p){
        //ID has to be different from the bodies read from the checkpoint file, so it is set to the number of bodies read from xml file
        id = static_cast<int>(numberOfBodiesReadFromCheckpoint);
        for (std::size_t i = 0; i < rhoLookUpTable.size(); ++i) {
            //the diagonal entries are the individual rho/epsilon values of the bodies
            valuesForLookUpRho[i] = rhoLookUpTable[i][i];
            valuesForLookUpEpsilon[i] = epsilonLookUpTable[i][i];
        }
        //particleCounter has to be set to avoid duplicate particle ID's
        particleCounter = static_cast<int>(CheckpointReader::particles.size());
    }

    for (auto & i : bodySequence) {
        valuesForLookUpRho[id] = i.rho();
        valuesForLookUpEpsilon[id] = i.epsilon();
        mass = i.mass();
        h = i.h();
        isMoving = [](bodyState x) { if (x == bodyState::moving) return true; else return false; }(i.bodyState());

        if (i.bodyType() == bodyType::Cuboid) {
            body = new Cuboid(id, h, mass, isMoving);
        } else if (i.bodyType() == bodyType::Tetrahedron) {
            body = new Tetrahedron(id, h, mass, isMoving);
        } else if (i.bodyType() == bodyType::Sphere) {
            body = new Sphere(id, h, mass, isMoving);
        } else if (i.bodyType() == bodyType::Membrane) {
            body = new Membrane(id, h, mass);
        } else {
            std::cout << "Parsing of XML-file was not successful!" << std::endl;
            std::cout << "Unknown body type." << std::endl;
            return false;
        }
        body->parsePosition(i.position());
        body->parseInitialV(i.velocity());
        try {
            body->parseStructure(i.objectSpecificFormat());
        } catch (const std::exception& e) {
            std::cout << "Parsing of XML-file was not successful!" << std::endl;
            std::cout << "Please check that correct path was provided." << std::endl;
            std::cout << "Please check that file was correctly formatted." << std::endl;
            return false;
        }

        body->generateParticles(particleCounter);
        particleCounter += body->getParticles().size();

        bodies.push_back(body);
        id++;
    }
    createLookUpTables();
    return true;
}

std::string BodyBuilder::toString() {
    std::string numberOfBodies = std::to_string(rhoLookUpTable.size()) + "\n";
    std::string outputString = numberOfBodies;
    for (const auto& v : rhoLookUpTable) {
        for (auto rho : v) {
            outputString += std::to_string(rho) + " ";
        }
    }
    outputString += "\n";
    for (const auto& v : epsilonLookUpTable) {
        for (auto epsilon : v) {
            outputString += std::to_string(epsilon) +  " ";
        }
    }
    return outputString + "\n";

}

void BodyBuilder::parseNumberOfBodies(const std::string& s) {
    int numberOfBodies = std::stoi(s);
    rhoLookUpTable.resize(numberOfBodies);
    epsilonLookUpTable.resize(numberOfBodies);
    for (int i = 0; i < numberOfBodies; ++i) {
        rhoLookUpTable[i].resize(numberOfBodies);
        epsilonLookUpTable[i].resize(numberOfBodies);
    }
}

void BodyBuilder::parseRhoLookupTable(const std::string& lookupTableString) {
    BodyBuilder::parseSingleLookupTable(rhoLookUpTable, lookupTableString);
}

void BodyBuilder::parseEpsilonLookupTable(const std::string& lookupTableString) {
    BodyBuilder::parseSingleLookupTable(epsilonLookUpTable, lookupTableString);
}

void BodyBuilder::parseSingleLookupTable(std::vector<std::vector<double>> &lookupTable, const std::string &lookupTableString){
    std::istringstream charStream(lookupTableString);
    for (int i = 0; i < static_cast<int>(lookupTable.size()); ++i) {
        for (int j = 0; j < static_cast<int>(lookupTable[i].size()); ++j) {
            charStream >> lookupTable[i][j];
        }
    }
}