#include <gtest/gtest.h>
#include "../XML_Parser/XMLParser.h"
#include "XML_Parser/BodyBuilder.h"

/**
 * @brief Test for checking if XML parser is working correctly
 */
TEST(GeneralTests, TestXMLParsing) {
    std::string filename = "../src/Tests/TestInputFiles/input_test.xml";
    bool success = XMLParser::parseXML(filename);
    std::list<Body*> bodies{};
    BodyBuilder::buildBodies(bodies, XMLParser::bodySequence);

    EXPECT_EQ(success, true);
    EXPECT_DOUBLE_EQ(XMLParser::t_end_p, 5);
    EXPECT_DOUBLE_EQ(XMLParser::delta_t_p, 0.0002);
    EXPECT_EQ(XMLParser::baseNameOutputFiles_p, "Lennard");
    EXPECT_EQ(XMLParser::writeFrequency_p, 100);
    EXPECT_EQ(XMLParser::gravInput_p, "../eingabe-sonne.txt");

    EXPECT_EQ(XMLParser::loadCheckpoint_p, false);

    EXPECT_DOUBLE_EQ(XMLParser::domainSize[1], 100);
    EXPECT_DOUBLE_EQ(XMLParser::cutoffRadius, 3);

    EXPECT_EQ(XMLParser::boundaryConditions[3], 3);

    EXPECT_EQ(bodies.size(), 2);
    EXPECT_EQ(bodies.back()->getInitialV()[1], -10);
}