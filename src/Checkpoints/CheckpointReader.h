#ifndef PSEMOLDYN_GROUPG_CHECKPOINTREADER_H
#define PSEMOLDYN_GROUPG_CHECKPOINTREADER_H

#include "ParticleContainers/ParticleContainerDirectSum.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include <string>

class CheckpointReader {
public:
    /**
     * @brief read checkpoint particles to start simulation with
     * @param fileName,particleContainer path of file of saved checkpoint particles and particleContainer to add the particles to
     * @return true if reading was successful, false otherwise
     */
    static bool readCheckpointFile(const std::string &fileName, ParticleContainer *particleContainer);

    /**
     * @brief vector for read particles
     */
    static std::vector<Particle> particles;

    /**
     * @brief variable to remember the calcType of read checkpoint particles
     */
    static int checkpointReadCalcType;

};


#endif //PSEMOLDYN_GROUPG_CHECKPOINTREADER_H
