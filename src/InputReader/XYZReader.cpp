//
// Created by thomas on 12.11.21.
//

#include "XYZReader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

bool XYZReader::readFile(const std::string &fileName) {
    std::ifstream input_file(fileName);
    std::string line;
    int numberElements;

    if (input_file.is_open()) {
        getline(input_file, line);
        std::istringstream iss(line);
        if(!(iss >> numberElements)) return false;
        //Skipp the next line
        getline(input_file, line);

        for (int i = 0; i < numberElements; i++) {
            getline(input_file, line);
            std::istringstream iss(line);
            if(!(iss >> std::get<0>(molecules[i]) >> std::get<1>(molecules[i])[0] >> std::get<1>(molecules[i])[1] >> std::get<1>(molecules[i])[2])) return false;
        }
    }
    return true;
}

const std::vector<std::tuple<std::string, std::array<double, 3>>> &XYZReader::getMolecules() const {
    return molecules;
}





