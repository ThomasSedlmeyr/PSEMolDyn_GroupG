#include <vector>
#include <gtest/gtest.h>
#include <InputReader/ArgumentContainer.h>
#include <vector>
#include <gtest/gtest.h>
#include "utils/FastMath.h"
#include <InputReader/ArgumentContainer.h>
#include <iostream>
#include <random>
#include "Example_Parser/Parser.h"


TEST(Tests, ParserTest1) {
    Parser p = Parser();
    p.main();
}
