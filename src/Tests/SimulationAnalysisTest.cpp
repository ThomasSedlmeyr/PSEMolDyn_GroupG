#include <vector>
#include <gtest/gtest.h>
#include "utils/FastMath.h"
#include "ParticleContainers/ParticleContainerLinkedCells.h"
#include "SimulationAnalysis/DiffusionAnalyzer.h"
#include "SimulationLogic/LennardJonesSimulation.h"
#include "OutputWriter/VTKWriter.h"
#include "SimulationAnalysis/RadialPairDistributionAnalyzer.h"
#include <random>
#include <fstream>
#include "SimulationAnalysis/VelocityProfileAnalyzer.h"

//Code adapted from
//https://stackoverflow.com/questions/28768359/comparison-of-floating-point-arrays-using-google-test-and-google-mock
#define EXPECT_DOUBLE_ARRAY_NEARLY_EQ(expected, actual, thresh) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            EXPECT_NEAR(expected[idx], actual[idx], thresh) << "at index: " << idx;\
        }

#define EXPECT_INT_ARRAY_EQ(expected, actual) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            EXPECT_EQ(expected[idx], actual[idx]) << "at index: " << idx;\
        }
/**
* @brief Tests the functionality of the DiffusionAnalyzer by reference values which were calculated by hand
*/
TEST(SimulationAnalysisTest, DiffusionCalculatorTest) {
    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(20, 40, 60, 3.0, fours);

    Particle p1 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 1);
    Particle p2 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 2);
    Particle p3 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 3);
    Particle p4 = Particle({1, 1, 1}, {1, 2, 3}, 23, -1, 4, false);
    p4.isGhostParticle = true;
    Particle p5 = Particle({1, 1, 1}, {1, 2, 3}, 23, -1, 5, false);
    p5.isGhostParticle = true;

    ParticleContainerLinkedCells::addParticle(p1);
    ParticleContainerLinkedCells::addParticle(p2);
    ParticleContainerLinkedCells::addParticle(p3);
    ParticleContainerLinkedCells::addParticle(p4);
    ParticleContainerLinkedCells::addParticle(p5);

    DiffusionAnalyzer df = DiffusionAnalyzer(&particleContainer);

    ParticleContainerLinkedCells::clearAllParticles();
    p1.setX({2,2,2});
    p2.setX({3,3,3});
    p3.setX({4,4,4});
    p4.setX({5,5,5});
    p5.setX({6,6,6});
    ParticleContainerLinkedCells::addParticle(p1);
    ParticleContainerLinkedCells::addParticle(p2);
    ParticleContainerLinkedCells::addParticle(p3);
    ParticleContainerLinkedCells::addParticle(p4);
    ParticleContainerLinkedCells::addParticle(p5);

    df.calculateDiffusion();
    EXPECT_NEAR(df.getDiffusion(), (3 + 12 + 27)*1.0/3.0 , 0.00001);
}

/**
* @brief Tests the functionality of the DiffusionAnalyzer by reference values which were calculated by hand
*/
TEST(SimulationAnalysisTest, RadialPairDistributionCalculator) {
    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(20, 40, 60, 3.0, fours);

    Particle p1 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 1);
    Particle p2 = Particle({2, 1.1, 1}, {1, 2, 3}, 23, 1, 2);
    Particle p3 = Particle({8, 1.2, 1}, {1, 2, 3}, 23, 1, 3);
    Particle p4 = Particle({1, 2, 4}, {1, 2, 3}, 23, 1, 4);

    ParticleContainerLinkedCells::addParticle(p1);
    ParticleContainerLinkedCells::addParticle(p2);
    ParticleContainerLinkedCells::addParticle(p3);
    ParticleContainerLinkedCells::addParticle(p4);

    RadialPairDistributionAnalyzer calculator = RadialPairDistributionAnalyzer(&particleContainer, 1, 1, 10,0,10);
    calculator.calculateLocalDensities();

    std::vector<int> numberOfParticlesInIntervall = calculator.getNumberParticlesInIntervall();
    std::vector<int> correctNumberOfParticlesInIntervall = {1,0,2,0,0,1,2,0,0,0};
    EXPECT_INT_ARRAY_EQ(numberOfParticlesInIntervall, correctNumberOfParticlesInIntervall);

    std::vector<double> localDensities = calculator.getLocalDensities();
    std::vector<double> correctDensities = {0.03410563066,0,0.01290445495,0,0,0.001879782792,0.002825235676,0,0,0};
    EXPECT_DOUBLE_ARRAY_NEARLY_EQ(correctDensities, localDensities, 0.000001);
}

/**
 * @brief quick test checking simulation analyzer writing to csv file
 */
TEST(SimulationAnalysisTest, checkOutputCSVFile) {
    bool xmlSuccess = XMLParser::parseXML("../src/Tests/TestInputFiles/SimulationAnalyzerTest.xml");
    EXPECT_EQ(xmlSuccess, true);

    LennardJonesSimulation lj = LennardJonesSimulation();
    Writer *w = new VTKWriter();
    std::array<int, 4> boundaryConditions = {XMLParser::right_p, XMLParser::left_p, XMLParser::top_p, XMLParser::bottom_p};
    ParticleContainer* particleContainer = new ParticleContainerLinkedCells(XMLParser::domainSize[0], XMLParser::domainSize[1], XMLParser::domainSize[2], XMLParser::cutoffRadius, XMLParser::boundaryConditions);

    VelocityProfileAnalyzer* analysis = new VelocityProfileAnalyzer(particleContainer);
    analysis->writeHeaderLineToCSVFile();

    lj.simulate(*w, particleContainer);

    //analysis->setParticleContainer(particleContainer);
    //analysis->appendLineToCSVFile();

    std::ifstream inFile;
    std::string tmp_string;
    inFile.open("../Analysis_Files/velocity_density.csv");
    bool writeSuccess = false;
    if (inFile.is_open()) {
        getline(inFile, tmp_string);
        getline(inFile, tmp_string);
        EXPECT_EQ(tmp_string, "0.347222,-0.252994,0.578704,-0.049028,0.578704,0.105072,0.578704,-0.138624,0.231481,-0.364036");
        writeSuccess = true;
        inFile.close();
    }
    EXPECT_EQ(writeSuccess, true);
}

/**
 * @brief test checking simulation analyzer calculation
 */
TEST(SimulationAnalysisTest, VelocityDensity) {
    std::array<int, 6> fours = {4, 4, 4, 4, 4, 4};
    ParticleContainerLinkedCells particleContainer(20, 40, 60, 3.0, fours);

    Particle p1 = Particle({1, 1, 1}, {1, 2, 3}, 23, 1, 1);
    Particle p2 = Particle({2, 1.1, 1}, {1, 2, 3}, 23, 1, 2);
    Particle p3 = Particle({11, 1.2, 1}, {1, -2, 3}, 23, 1, 3);
    Particle p4 = Particle({14, 2, 4}, {1, 2, 3}, 23, 1, 4);
    Particle p5 = Particle({19, 2, 4}, {0, 0, 0}, 23, 1, 5);
    Particle p6 = Particle({19, 16, 4}, {0, -1, 0}, 23, 1, 6);

    ParticleContainerLinkedCells::addParticle(p1);
    ParticleContainerLinkedCells::addParticle(p2);
    ParticleContainerLinkedCells::addParticle(p3);
    ParticleContainerLinkedCells::addParticle(p4);
    ParticleContainerLinkedCells::addParticle(p5);
    ParticleContainerLinkedCells::addParticle(p6);

    XMLParser::domainSize[0] = 20;
    XMLParser::domainSize[1] = 40;
    XMLParser::domainSize[2] = 60;
    XMLParser::numberOfBins_p = 4;
    VelocityProfileAnalyzer* analysis = new VelocityProfileAnalyzer(&particleContainer);
    analysis->calculateVelocityAndDensityProfile();
    std::string result = analysis->calculationResultsToString();
    EXPECT_EQ(result, "0.000167,2.000000,0.000000,0.000000,0.000167,0.000000,0.000083,-1.000000");
}