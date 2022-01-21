//
// Created by daniel on 21.01.22.
//

#include <vector>
#include <gtest/gtest.h>
#include "Checkpoints/CheckpointReader.h"
#include "SimulationLogic/Simulation.h"
#include "ParticleContainers/ParticleContainer.h"
#include "Checkpoints/CheckpointWriter.h"
#include "XML_Parser/XMLParser.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "2D/ParticleContainerLinkedCells2D.h"
#include "OutputWriter/VTKWriter.h"

/**
 * @brief quick test checking simulation analyzer writing to csv file
 */
TEST(AnalyzerTests, checkSimulationAnalyzerOutput) {
    bool xmlSuccess = XMLParser::parseXML("../src/Tests/TestInputFiles/SimulationAnalzyerTest.xml");
    EXPECT_EQ(xmlSuccess, true);

    LennardJonesSimulation lj = LennardJonesSimulation();
    Writer *w = new VTKWriter();
    std::array<int, 4> boundaryConditions = {XMLParser::right_p, XMLParser::left_p, XMLParser::top_p, XMLParser::bottom_p};
    ParticleContainer* particleContainer = new ParticleContainerLinkedCells(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::domainSize[2], XMLParser::cutoffRadius, XMLParser::boundaryConditions);
    lj.simulate(*w, particleContainer);

    // TODO check correctnes of csv file after SimulationAnalyzer has been incorporated into simulation
}