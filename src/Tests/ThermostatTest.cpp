//
// Created by philip on 22.12.21.
//

#include <gtest/gtest.h>
#include <XML_Parser/XMLParser.h>
#include <XML_Parser/BodyBuilder.h>
#include <SimulationLogic/LennardJonesSimulation.h>
#include <OutputWriter/VTKWriter.h>
#include "SimulationLogic/Thermostat.h"
#include "ParticleContainers/ParticleContainerDirectSum.h"

TEST(ThemostatTests, TestSetTemp){
    std::string filename = "../src/Tests/TestInputFiles/input_test.xml";
    XMLParser::parseXML(filename);
    std::list<Body*> bodies{};
    BodyBuilder::buildBodies(bodies, XMLParser::bodySequence);
    ParticleContainerDirectSum pc;
    for (Body *body : bodies) {
        for (Particle p : body->getParticles()) {
            pc.addParticleToContainer(p);
        }
    }
    for (int i = 1; i < 100; ++i) {
        Thermostat t = Thermostat(&pc, i, 3);
        t.apply();
        //test if thermostat worked
        KineticEnergyVisitor energyVisitor;
        MeanVelocityVisitor meanVelocityVisitor;
        pc.walkOverParticles(meanVelocityVisitor);
        pc.walkOverParticles(energyVisitor);
        double currentTemp = energyVisitor.getTotalEnergy() / (double(meanVelocityVisitor.getNumberOfParticles()) * 3 / 2);
        ASSERT_NEAR(currentTemp, i, 0.0001);
    }
}
TEST(ThemostatTests, TestHoldTemp){
    std::string filename = "../src/Tests/TestInputFiles/ThermostatHoldTempInput.xml";
    XMLParser::parseXML(filename);
    LennardJonesSimulation lj = LennardJonesSimulation();
    ParticleContainerDirectSum pc = ParticleContainerDirectSum();
    VTKWriter w = VTKWriter();
    lj.simulate(w, &pc);
    //test if thermostat worked
    MeanVelocityVisitor meanVelocityVisitor;
    pc.walkOverParticles(meanVelocityVisitor);
    KineticEnergyVisitor energyVisitor;
    pc.walkOverParticles(energyVisitor);
    double currentTemp = energyVisitor.getTotalEnergy() / (double(meanVelocityVisitor.getNumberOfParticles()) * 2 / 2);
    ASSERT_NEAR(currentTemp, 10.0, 0.1);

}

TEST(ThemostatTests, TestCoolDown){
    std::string filename = "../src/Tests/TestInputFiles/ThermostatCoolInput.xml";
    XMLParser::parseXML(filename);
    LennardJonesSimulation lj = LennardJonesSimulation();
    ParticleContainerDirectSum pc = ParticleContainerDirectSum();
    VTKWriter w = VTKWriter();
    lj.simulate(w, &pc);
    //test if thermostat worked
    MeanVelocityVisitor meanVelocityVisitor;
    pc.walkOverParticles(meanVelocityVisitor);
    KineticEnergyVisitor energyVisitor;
    pc.walkOverParticles(energyVisitor);
    double currentTemp = energyVisitor.getTotalEnergy() / (double(meanVelocityVisitor.getNumberOfParticles()) * 2 / 2);
    ASSERT_NEAR(currentTemp, 1.0, 0.1);
}

TEST(ThemostatTests, TestHeatUp){
    std::string filename = "../src/Tests/TestInputFiles/ThermostatHeatInput.xml";
    XMLParser::parseXML(filename);
    LennardJonesSimulation lj = LennardJonesSimulation();
    ParticleContainerDirectSum pc = ParticleContainerDirectSum();
    VTKWriter w = VTKWriter();
    lj.simulate(w, &pc);
    //test if thermostat worked
    MeanVelocityVisitor meanVelocityVisitor;
    pc.walkOverParticles(meanVelocityVisitor);
    KineticEnergyVisitor energyVisitor;
    pc.walkOverParticles(energyVisitor);
    double currentTemp = energyVisitor.getTotalEnergy() / (double(meanVelocityVisitor.getNumberOfParticles()) * 2 / 2);
    ASSERT_NEAR(currentTemp, 32.0, 0.1);
}
