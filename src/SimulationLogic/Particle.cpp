/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"
#include "utils/ArrayUtils.h"
#include <iostream>
#include "XML_Parser/XMLParser.h"
#include "SimulationLogic/Simulation.h"

Particle::Particle(int type_arg) {
  type = type_arg;
  //std::cout << "Particle generated!" << std::endl;
  f = {0., 0., 0.};
  old_f = {0., 0., 0.};
}

Particle::Particle(const Particle &other) {
  x = other.x;
  v = other.v;
  f = other.f;
  old_f = other.old_f;
  m = other.m;
  type = other.type;
  ID = other.ID;
  isGhostParticle = other.isGhostParticle;
  movingIsAllowed = other.movingIsAllowed;
  neighbourIDs = other.neighbourIDs;
  directNeighbourIDs = other.directNeighbourIDs;
  numberOfTimesCrossedWholeDomain = other.numberOfTimesCrossedWholeDomain;
  isPartOfMembrane = other.isPartOfMembrane;
  //std::cout << "Particle generated by copy!" << std::endl;
}

Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, int type_arg, int id_arg, bool movingIsAllowed_arg) {
  x = x_arg;
  v = v_arg;
  m = m_arg;
  type = type_arg;
  f = {0., 0., 0.};
  old_f = {0., 0., 0.};
  ID = id_arg;
  movingIsAllowed = movingIsAllowed_arg;
  numberOfTimesCrossedWholeDomain = {0,0,0};
  //std::cout << "Particle generated!" << std::endl;
}

// new constructor for checkpoints
Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, int type_arg, std::array<double, 3> f_arg, std::array<double, 3> f_old_arg, int id_arg) {
    x = x_arg;
    v = v_arg;
    m = m_arg;
    type = type_arg;
    f = f_arg;
    old_f = f_old_arg;
    ID = id_arg;
}

Particle::~Particle() { //std::cout << "Particle destructed!" << std::endl;
     }

const std::array<double, 3> &Particle::getX() const { return x; }

const std::array<double, 3> &Particle::getV() const { return v; }

const std::array<double, 3> &Particle::getF() const { return f; }

const std::array<double, 3> &Particle::getOldF() const { return old_f; }

double Particle::getM() const { return m; }

int Particle::getType() const { return type; }

void Particle::setX(const std::array<double, 3> &x) {
    Particle::x = x;
}

void Particle::setV(const std::array<double, 3> &v) {
    Particle::v = v;
}

void Particle::setF(const std::array<double, 3> &f) {
    Particle::f = f;
}

void Particle::setOldF(const std::array<double, 3> &oldF) {
    old_f = oldF;
}

void Particle::prepareForNewForce() {
    old_f = f;
    std::fill(f.begin(), f.end(), 0);
}

std::string Particle::toString() const {
  std::stringstream stream;
  stream << "Particle: X:" << x << " v: " << v << " f: " << f
         << " old_f: " << old_f << " type: " << type;
  return stream.str();
}

bool Particle::operator==(Particle &other) {
  return (x == other.x) and (v == other.v) and (f == other.f) and
         (type == other.type) and (m == other.m) and (old_f == other.old_f);
}

bool Particle::operator==(const Particle& other) {
    return (x == other.x) and (v == other.v) and (f == other.f) and
           (type == other.type) and (m == other.m) and (old_f == other.old_f);
}

std::array<double, 3> &Particle::getFRef() {
    return f;
}

int Particle::getId() const {
    return ID;
}

std::array<double, 3> &Particle::getVRef() {
    return v;
}

std::array<double, 3> &Particle::getXRef() {
    return x;
}

std::string Particle::toString() {
    std::string ret;
    ret = std::to_string(x[0]) + " " + std::to_string(x[1]) + " " + std::to_string(x[2])
          + "\t" + std::to_string(v[0]) + " " + std::to_string(v[1]) + " " + std::to_string(v[2])
          + "\t" + std::to_string(m) + "\t" + std::to_string(type) + "\t" + std::to_string(f[0])
          + " " + std::to_string(f[1]) + " " + std::to_string(f[2]) + "\t" + std::to_string(old_f[0])
          + " " + std::to_string(old_f[1]) + " " + std::to_string(old_f[2]) + "\t" + std::to_string(ID)
          + "\t" + std::to_string(isPartOfMembrane) + "\t" + std::to_string(numberOfTimesCrossedWholeDomain[0])
          + " " + std::to_string(numberOfTimesCrossedWholeDomain[1]) + " "
          + std::to_string(numberOfTimesCrossedWholeDomain[2]);
    return ret;
}

void Particle::setIsGhostParticle(const bool &b) {
    isGhostParticle = b;
}

bool Particle::getMovingAllowed() const{
    return movingIsAllowed;
}

void Particle::addParticleToNeighbours(const int neighbourID) {
    if (neighbourID >= 0){
        neighbourIDs.push_back(neighbourID);
    }
}

void Particle::addParticleToDirectNeighbours(const int neighbourID) {
    if (neighbourID >= 0){
        directNeighbourIDs.push_back(neighbourID);
    }
}

bool Particle::particlesAreNeighbours(const Particle &p1, const Particle &p2) {
    return std::find(p2.getNeighbourIDs().begin(), p2.getNeighbourIDs().end(), p1.getId()) != p2.getNeighbourIDs().end();
}

bool Particle::particlesAreDirectNeighbours(const Particle &p1, const Particle &p2) {
    return std::find(p2.getDirectNeighbourIDs().begin(), p2.getDirectNeighbourIDs().end(), p1.getId()) != p2.getDirectNeighbourIDs().end();
}

const std::vector<int> &Particle::getDirectNeighbourIDs() const {
    return directNeighbourIDs;
}

const std::vector<int> &Particle::getNeighbourIDs() const {
    return neighbourIDs;
}

void Particle::decrementNumberOfTimesCrossedDomainX() {
    numberOfTimesCrossedWholeDomain[0]--;
}

void Particle::decrementNumberOfTimesCrossedDomainY() {
    numberOfTimesCrossedWholeDomain[1]--;
}

void Particle::decrementNumberOfTimesCrossedDomainZ() {
    numberOfTimesCrossedWholeDomain[2]--;
}

void Particle::incrementNumberOfTimesCrossedDomainX() {
    numberOfTimesCrossedWholeDomain[0]++;
}

void Particle::incrementNumberOfTimesCrossedDomainY() {
    numberOfTimesCrossedWholeDomain[1]++;
}

void Particle::incrementNumberOfTimesCrossedDomainZ() {
    numberOfTimesCrossedWholeDomain[2]++;
}

const std::array<short, 3> &Particle::getNumberOfTimesCrossedWholeDomain() const {
    return numberOfTimesCrossedWholeDomain;
}

void Particle::setNumberOfTimesCrossedWholeDomain(const std::array<short, 3> &numberOfTimesCrossedWholeDomain) {
    Particle::numberOfTimesCrossedWholeDomain = numberOfTimesCrossedWholeDomain;
}

std::ostream &operator<<(std::ostream &stream, Particle &p) {
    stream << p.toString();
    return stream;
}

std::array<double, 3> Particle::getRealPosition(){
    std::array<double, 3> realPosition = {0,0,0};
    realPosition[0] = x[0] + numberOfTimesCrossedWholeDomain[0] * ParticleContainerLinkedCells::domainSizeX;
    realPosition[1] = x[1] + numberOfTimesCrossedWholeDomain[1] * ParticleContainerLinkedCells::domainSizeY;
    realPosition[2] = x[2] + numberOfTimesCrossedWholeDomain[2] * ParticleContainerLinkedCells::domainSizeZ;
    return realPosition;
}