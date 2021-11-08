/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "SimulationLogic/Particle.h"
#include "Writer.h"

#include <fstream>
#include <list>
#include <vector>

class XYZWriter: public Writer {

public:
  XYZWriter();

  virtual ~XYZWriter();

  void plotParticles(std::vector<Particle> particles, const std::string &filename, int iteration);
  void writeParticlesToFile(const std::string &filename, int iteration, const std::vector<Particle> &particles);
};


