//
// Created by daniel on 27.01.22.
//

#ifndef PSEMOLDYN_GROUPG_CSVWRITER_H
#define PSEMOLDYN_GROUPG_CSVWRITER_H

#include "Writer.h"

class CSVWriter{

public:
    CSVWriter();
    ~CSVWriter();

    void writeToFile(const std::string &path, const std::string &line);

    void createCSV(const std::string &path);
};


#endif //PSEMOLDYN_GROUPG_CSVWRITER_H
