//
// Created by daniel on 27.01.22.
//

#include "CSVWriter.h"
#include <fstream>


CSVWriter::CSVWriter() {

}
CSVWriter::~CSVWriter(){}

void CSVWriter::createCSV(const std::string &path) {
    std::ofstream outputFile;
    outputFile.open(path, std::ios::trunc);
    outputFile.close();
}

void CSVWriter::writeToFile(const std::string &path, const std::string &line) {
    std::ofstream outputFile;
    outputFile.open(path, std::ios::app);
    outputFile << line << "\n";
    outputFile.close();
}
