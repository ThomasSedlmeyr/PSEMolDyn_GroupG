//
// Created by thomas on 29.12.21.
//

#include <Visitors/LJForceVisitor.h>
#include <Visitors/UpwardForceVisitor.h>
#include <iostream>
#include "Membrane.h"

void Membrane::parseStructure(const std::string &line) {

    std::string n_p = "";
    std::string r_p = "";
    std::string k_p = "";
    std::string fUp_p = "";
    std::string p_p = "";
    std::string tmp = line;

    int begin = 2;
    int end = tmp.find_first_of(" ");
    if (tmp.substr(0, 1) == "n") {
        n_p = tmp.substr(begin, end - begin);
        tmp.erase(0, end + 1);
    } else {
        std::cout << "Parsing of membrane was not successful!" << std::endl;
        std::cout << "Please make sure to format the parameters according to the README." << std::endl;
        throw std::runtime_error("");
    }

    end = tmp.find_first_of(" ");
    if (tmp.substr(0, 1) == "r") {
        r_p = tmp.substr(begin, end - begin);
        tmp.erase(0, end + 1);
    } else {
        std::cout << "Parsing of membrane was not successful!" << std::endl;
        std::cout << "Please make sure to format the parameters according to the README." << std::endl;
        throw std::runtime_error("");
    }

    end = tmp.find_first_of(" ");
    if (tmp.substr(0, 1) == "k") {
        k_p = tmp.substr(begin, end - begin);
        tmp.erase(0, end + 1);
    } else {
        std::cout << "Parsing of membrane was not successful!" << std::endl;
        std::cout << "Please make sure to format the parameters according to the README." << std::endl;
        throw std::runtime_error("");
    }

    if (!tmp.empty()) {
        end = tmp.find_first_of(" ");
        if (tmp.substr(0, 1) == "f") {
            fUp_p = tmp.substr(begin, end - begin);
            tmp.erase(0, end + 1);
        } else {
            std::cout << "Parsing of membrane was not successful!" << std::endl;
            std::cout << "Please make sure to format the parameters according to the README." << std::endl;
            throw std::runtime_error("");
        }

        end = tmp.find_first_of(" ");
        if (tmp.substr(0, 1) == "p") {
            p_p = tmp.substr(begin, end - begin);
            tmp.erase(0, end + 1);
        } else {
            std::cout << "Parsing of membrane was not successful!" << std::endl;
            std::cout << "Please make sure to format the parameters according to the README." << std::endl;
            throw std::runtime_error("");
        }
    } else {
        fUp = 0;
        positionsWhereFisApplied = {{0,0}};
    }

    dimensions = parseLineWithThreeValues(n_p);
    r_zero = std::stod(r_p);
    k = std::stod(k_p);
    fUp = std::stod(fUp_p);

    int first;
    int comma;
    int second;
    int bracket;
    std::array<int, 2> arr = {};
    while (!p_p.empty()) {
        if (p_p.substr(0, 1) == ",") {
            p_p.erase(0, 2);
        } else {
            p_p.erase(0, 1);
        }
        p_p.erase(0, 1);
        comma = p_p.find_first_of(",");
        bracket = p_p.find_first_of(")");
        first = std::stoi(p_p.substr(0, comma));
        second = std::stoi(p_p.substr(comma + 1, bracket - (comma + 1)));
        p_p.erase(0, bracket + 1);
        arr = {first, second};
        positionsWhereFisApplied.push_back(arr);
    }
}

void Membrane::generateParticles(int startIndex) {
    particles = std::vector<Particle>(dimensions[0] * dimensions[1] * dimensions[2]);
    std::array<double, 3> newPosition{};
    int counter = 0;
    for (int i = 0; i < dimensions[0]; ++i) {
        for (int j = 0; j < dimensions[1]; ++j) {
            for (int l = 0; l < dimensions[2]; ++l) {
                newPosition[0] = position[0] + meshWidth * i;
                newPosition[1] = position[1] + meshWidth * j;
                newPosition[2] = position[2] + meshWidth * l;
                particles[counter] = Particle(newPosition, initialV, massPerParticle, ID, startIndex, movingIsAllowed);
                startIndex++;
                counter++;
            }
        }
    }
    setNeighbourParticles();
    setParticlesWhereFisApplied();
}

Membrane::Membrane(int ID, double meshWidth, double massPerParticle) : Body(ID, meshWidth, massPerParticle) {
    LJForceVisitor::membraneIDs.push_back(ID);
    /*
    positionsWhereFisApplied = {{17,24},{17,25},{18,24},{18,25}};
    */

}

Membrane::~Membrane() {}

void Membrane::setParticlesWhereFisApplied() {
    for(auto& position : positionsWhereFisApplied){
        int index = position[0] + position[1] * dimensions[0];
        UpwardForceVisitor::particlesWithFZUp.push_back(particles[index].getId());
    }
}

void Membrane::setNeighbourParticles() {
    for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
        auto topNeighbour = i + int(dimensions[0]);
        auto bottomNeighbour = i - int(dimensions[0]);
        if (topNeighbour >= particles.size()){
            topNeighbour = -2;
        }
        if (bottomNeighbour < 0){
            bottomNeighbour = -2;
        }

        //Vertical neighbours
        particles[i].addParticleToNeighbours(topNeighbour);
        particles[i].addParticleToNeighbours(bottomNeighbour);

        particles[i].addParticleToDirectNeighbours(topNeighbour);
        particles[i].addParticleToDirectNeighbours(bottomNeighbour);

        if (i % int(dimensions[0]) != 0){
            //Not on left edge
            particles[i].addParticleToNeighbours(i-1);
            particles[i].addParticleToDirectNeighbours(i-1);
            //diagonal neighbours
            particles[i].addParticleToNeighbours(topNeighbour - 1);
            particles[i].addParticleToNeighbours(bottomNeighbour - 1);
        }

        if ((i + 1) % int(dimensions[0]) != 0){
            //Not on right edge
            particles[i].addParticleToNeighbours(i+1);
            particles[i].addParticleToDirectNeighbours(i+1);
            //diagonal neighbours
            particles[i].addParticleToNeighbours(topNeighbour + 1);
            particles[i].addParticleToNeighbours(bottomNeighbour + 1);
        }
    }
}