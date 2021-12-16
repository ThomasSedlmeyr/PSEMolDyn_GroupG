#ifndef PSEMOLDYN_GROUPG_CHECKPOINTREADER_H
#define PSEMOLDYN_GROUPG_CHECKPOINTREADER_H

#include "ParticleContainers/ParticleContainerDirectSum.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include <string>

class CheckpointReader {
public:
    /**
     * @brief read checkpoint particles to start simulation with
     * @param fileName path of file of saved checkpoint particles
     * @return true if reading was successful, false otherwise
     */
    static bool readCheckpointFile(const std::string &fileName);

    /**
     * @brief container for all read particles
     */
    static ParticleContainer *particleContainer;

    /**
     * @brief variable to remember the calcType of read checkpoint particles
     */
    static int checkpointReadCalcType;

    // TODO static void resetCheckpointReaderData();
};


#endif //PSEMOLDYN_GROUPG_CHECKPOINTREADER_H
