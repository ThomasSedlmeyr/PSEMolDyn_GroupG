//
// Created by daniel on 15.12.21.
//

#ifndef PSEMOLDYN_GROUPG_CHECKPOINTWRITER_H
#define PSEMOLDYN_GROUPG_CHECKPOINTWRITER_H

#include <string>
#include "ParticleContainers/ParticleContainer.h"

class CheckpointWriter {
public:
    /**
     * @brief write checkpoint particles to output file
     * @param fileName path of output file
     */
    static bool writeCheckpointFile(const std::string &fileName, ParticleContainer *particleContainer);
};


#endif //PSEMOLDYN_GROUPG_CHECKPOINTWRITER_H
