#include <vector>
#include <gtest/gtest.h>
#include "utils/FastMath.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include "SimulationAnalysis/DiffusionCalculator.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "OutputWriter/VTKWriter.h"
#include <random>


/**
* @brief Tests the functionality of the DiffusionCalculator by reference values which were calculated by hand
*/
TEST(SimulationAnalysisTest, DiffusionCalculatorTest) {
    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(20, 40, 60, 3.0, fours);

    Particle p1 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 1);
    Particle p2 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 2);
    Particle p3 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 3);
    Particle p4 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 4);
    Particle p5 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 5);
    Particle p6 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 6);

    ParticleContainerLinkedCells::addParticle(p1);
    ParticleContainerLinkedCells::addParticle(p2);
    ParticleContainerLinkedCells::addParticle(p3);
    ParticleContainerLinkedCells::addParticle(p4);
    ParticleContainerLinkedCells::addParticle(p5);
    ParticleContainerLinkedCells::addParticle(p6);

    //DiffusionCalculator df;

    p2.setX({2,2,2});
    p3.setX({3,3,3});
    p4.setX({4,4,4});

    //df.calculateDiffusion();
}

/**
 * @brief quick test checking simulation analyzer writing to csv file
 */
TEST(SimulationAnalysisTest, checkOutputCSVFile) {
    bool xmlSuccess = XMLParser::parseXML("../src/Tests/TestInputFiles/SimulationAnalzyerTest.xml");
    EXPECT_EQ(xmlSuccess, true);

    LennardJonesSimulation lj = LennardJonesSimulation();
    Writer *w = new VTKWriter();
    std::array<int, 4> boundaryConditions = {XMLParser::right_p, XMLParser::left_p, XMLParser::top_p, XMLParser::bottom_p};
    ParticleContainer* particleContainer = new ParticleContainerLinkedCells(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::domainSize[2], XMLParser::cutoffRadius, XMLParser::boundaryConditions);
    lj.simulate(*w, particleContainer);

    // TODO check correctnes of csv file after SimulationAnalyzer has been incorporated into simulation
}