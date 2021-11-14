//
// Created by thomas on 12.11.21.
//

#include "XYZReader.h"
#include <fstream>

/*bool XYZReader::readFile(const std::string &fileName) {

    std::ifstream input_file(fileName);
    std::string tmp_string;

    if (input_file.is_open()) {

        getline(input_file, tmp_string);
        std::cout << "Read line: " << tmp_string << std::endl;

        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
            std::cout << "Read line: " << tmp_string << std::endl;
        }

        std::istringstream numstream(tmp_string);

        for (int i = 0; i < num_particles; i++) {
            std::istringstream datastream(tmp_string);

            for (auto &xj: x) {
                datastream >> xj;
            }
            for (auto &vj: v) {
                datastream >> vj;
            }
            if (datastream.eof()) {
                std::cout
                        << "Error reading file: eof reached unexpectedly reading from line "
                        << i << std::endl;
                exit(-1);
            }
    }
}





    size_t pos = 0;
    std::string token;
    while ((pos = line.find(" ")) != std::string::npos) {
        token = line.substr(0, pos);
        std::cout << token << std::endl;
        line.erase(0, pos + 1);
    }
    std::cout << line << std::endl;
*/