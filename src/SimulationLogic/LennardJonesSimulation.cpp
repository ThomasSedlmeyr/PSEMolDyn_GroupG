//
// Created by thomas on 07.11.21.
//

#include "LennardJonesSimulation.h"
#include "utils/ArrayUtils.h"
#include "Cuboid.h"
#include <string>
#include <list>

void LennardJonesSimulation::calculateF() {
    //TODO geht nicht wegen Referenzen?
    auto particles = particleContainer.getParticles();
    for (auto p1 = particles.begin(); p1 != particles.end(); ++p1){
        for (auto p2 = p1 + 1; p2 != particles.end(); ++p2){
            auto norm = ArrayUtils::L2Norm(p1->getX() - p2->getX());
            double term1 = -24*epsilon/pow(norm, 2);
            double term2 =  pow(rho/norm, 6);
            double term3 =  term2 - 2 * pow(term2, 2);
            auto result = term1 * term3 * (p2->getX() - p1->getX());
            p1->setOldF(p1->getF());
            p1->setF(p1->getF()+result);
            p2->setOldF(p2->getF());
            p2->setF(p2->getF()-result);
        }
    }
}

void LennardJonesSimulation::readParticles(const std::string &filename) {
    //TODO hier müsste mit irgendeinem Writer Zeile für Zeile die Datei eingelesen werden

    for(int i=0; i< 4; i++){
        std::string line = "Cuboid"; //readLine()
        Body *body;
        if(line.compare("Cuboid")){
            body = new Cuboid();
        }
        line = "0,0,0"; //readLine()
        body->parsePosition(line);
        line = "0,0,0"; //readLine()
        body->parseInitialV(line);
        line = "40,8,1"; //readLine()
        body->parseStructure(line);
        bodies.push_back(body);
    }

    //TODO hier sollen die einzelnen Bodies dann ihre Partikel erstellen und dem Particel Container übergeben
    //ich glaube aus Performancegründen ist es wichtig das die Partikel alle hintereinander im Speicher stehen
}

void LennardJonesSimulation::setParamsWithValues() {
    epsilon = argumentContainer.getValueToParam("epsilon");
    mass = argumentContainer.getValueToParam("mass");
    rho = argumentContainer.getValueToParam("rho");
    h = argumentContainer.getValueToParam("h");

}

void LennardJonesSimulation::initializeParamNames() {
    paramNames = {"epsilon", "mass", "rho", "h"};
}


