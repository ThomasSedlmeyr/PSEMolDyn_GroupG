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

    Writer(const std::string &fileName);

    virtual ~Writer();
    virtual void writeParticlesToFile(const std::string &filename, int iteration, const std::vector<Particle> &particles);

};


#endif //PSEMOLDYN_GROUPG_WRITER_H
