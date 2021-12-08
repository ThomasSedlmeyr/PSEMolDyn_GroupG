#include <gtest/gtest.h>
#include "../XML_Parser/XMLParser.h"

/**
 * @brief Test for checking if XML parser is working correctly
 */
TEST(Tests, parseXMLTest) {
    std::string filename = "../src/Tests/TestInputFiles/input_test.xml";
    XMLParser::parseXML(filename);
    EXPECT_DOUBLE_EQ(XMLParser::t_end_p, 5);
    EXPECT_DOUBLE_EQ(XMLParser::delta_t_p, 0.0002);
    EXPECT_EQ(XMLParser::baseNameOutputFiles_p, "Lennard");
    EXPECT_EQ(XMLParser::writeFrequency_p, 100);
    EXPECT_EQ(XMLParser::gravInput_p, "../eingabe-sonne.txt");

    EXPECT_DOUBLE_EQ(XMLParser::epsilon_p, 5.0);
    EXPECT_DOUBLE_EQ(XMLParser::domainSize[1], 100);
    EXPECT_DOUBLE_EQ(XMLParser::cutoffRadius, 3);

    EXPECT_EQ(XMLParser::boundaryConditions[3], 3);

    EXPECT_EQ(XMLParser::bodies_p.size(), 2);
    EXPECT_EQ(XMLParser::bodies_p.back()->getInitialV()[1], -10);
    EXPECT_EQ(XMLParser::bodies_p.back()->getMeshWidth(), XMLParser::h_p);
}