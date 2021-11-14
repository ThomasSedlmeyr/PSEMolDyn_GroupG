//file
// Created by thomas on 11.11.21.
//

#include <SimulationLogic/GravitationSimulation.h>
#include <outputWriter/XYZWriter.h>
#include "GravitationSimulationTest.h"

bool GravitationSimulationTest::testWholeSimulationProcess() {
    auto s = GravitationSimulation();
    Writer *w = new XYZWriter();
    s.simulate(1, 0.01, *w, 10, "", "../src/Test/ReferenceTestFiles", "Grav");
}
