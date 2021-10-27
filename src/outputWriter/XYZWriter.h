/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "Particle.h"

#include <fstream>
#include <list>
#include <vector>

namespace outputWriter {

class XYZWriter {

public:
  XYZWriter();

  virtual ~XYZWriter();

  void plotParticles(std::vector<Particle> particles, const std::string &filename,
                     int iteration);
};

} // namespace outputWriter
