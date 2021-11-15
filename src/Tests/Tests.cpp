//
// Created by thomas on 07.11.21.
//

#include "Tests.h"
#include <vector>
#include <string>
#include <tuple>
#include <InputReader/XYZReader.h>


bool Tests::testForce() {
    XYZReader reader = XYZReader();
    if(!reader.readFile("../Tests/ReferenceTestFiles/MD_vtk_0500.xyz")) return false;
    std::vector<std::tuple<std::string,std::array<double, 3>>> molecules = reader.getMolecules();
}

