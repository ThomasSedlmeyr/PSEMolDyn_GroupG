//
// Created by thomas on 05.11.21.
//

#ifndef PSEMOLDYN_GROUPG_WRITER_H
#define PSEMOLDYN_GROUPG_WRITER_H


#include <string>
#include <SimulationLogic/Particle.h>
#include <vector>

class Writer {
private:
    std::string fileName;
public:
    Writer();
    virtual ~Writer();

    /**
     * @brief writes the particles of specific simulation time step to a file
     *
     * @param filename the name of the File which should be created
     * @param iteration the current iteration in the simulation process
     * @param particles the particles which should be written to the file
     */
    virtual void writeParticlesToFile(const std::string &filename, int iteration, const std::vector<Particle> &particles) = 0;

};


#endif //PSEMOLDYN_GROUPG_WRITER_H
