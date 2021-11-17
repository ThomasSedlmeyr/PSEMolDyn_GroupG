//
// Created by thomas on 12.11.21.
//

#include "XYZReader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <iostream>

std::vector<std::tuple<std::string, std::array<double, 3>>>  XYZReader::readParticles(const std::string &fileName) {
    std::ifstream input_file(fileName);
    std::string line;
    int numberElements;
    //std::vector<std::tuple<std::string,std::array<double, 3>>> molecules;
    std::vector<std::tuple<std::string,std::array<double, 3>>> molecules;
    if (input_file.is_open()) {
        getline(input_file, line);
        std::istringstream iss(line);
        if(!(iss >> numberElements)) throw std::runtime_error("Error by reading the file: " +  fileName);

        //Skipp the next line
        getline(input_file, line);

        molecules = std::vector<std::tuple<std::string, std::array<double, 3>>>(numberElements);
        for (int i = 0; i < numberElements; i++) {
            getline(input_file, line);
            std::istringstream iss(line);
            if (!(iss >> std::get<0>(molecules[i]) >> std::get<1>(molecules[i])[0] >> std::get<1>(molecules[i])[1] >> std::get<1>(molecules[i])[2])) {
                throw std::runtime_error("Error by reading the file: " + fileName +  "at line: " + std::to_string(i+3));
            }
        }
    }else{
        throw std::runtime_error("Could not open file: " + fileName);
    }
    return molecules;
}

std::vector<std::array<double, 3>> XYZReader::readOnlyPositions(const std::string &fileName) {
    std::ifstream input_file(fileName);
    std::string line;
    int numberElements;
    //std::vector<std::tuple<std::string,std::array<double, 3>>> molecules;
    std::vector<std::array<double, 3>> positions;
    if (input_file.is_open()) {
        getline(input_file, line);
        std::istringstream iss(line);
        if(!(iss >> numberElements)) throw std::runtime_error("Error by reading the file: " +  fileName);

        //Skipp the next line
        getline(input_file, line);
        positions = std::vector<std::array<double, 3>>(numberElements);
        std::string dummyElement;

        for (int i = 0; i < numberElements; i++) {
            getline(input_file, line);
            std::istringstream iss(line);
            if (!(iss >> dummyElement >> positions[i][0] >> positions[i][1] >> positions[i][2])) {
                throw std::runtime_error("Error by reading the file: " + fileName +  "at line: " + std::to_string(i+3));
            }
        }
    }else{
        throw std::runtime_error("Could not open file: " + fileName);
    }
    return positions;
}






