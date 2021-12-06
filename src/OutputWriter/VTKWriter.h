/*
 * VTKWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "SimulationLogic/Particle.h"
#include "OutputWriter/vtk-unstructured.h"
#include "Writer.h"
#include <list>


/**
 * This class implements the functionality to generate vtk output from
 * particles.
 */
class VTKWriter: public Writer{

public:
  VTKWriter();
  ~VTKWriter() override;

  void writeParticlesToFile(const std::string &filename, int iteration, const std::vector<Particle> &particles) override;

  /**
   * set up internal data structures and prepare to plot a particle.
   */
  void initializeOutput(int numParticles);

  /**
   * plot type, mass, position, velocity and force of a particle.
   *
   * @note: initializeOutput() must have been called before.
   */
  void plotParticle(Particle &p);

  /**
   * writes the final output file.
   *
   * @param filename the base name of the file to be written.
   * @param iteration the number of the current iteration,
   *        which is used to generate an unique filename
   */
  void writeFile(const std::string &filename, int iteration);

private:
  VTKFile_t *vtkFile;
};


