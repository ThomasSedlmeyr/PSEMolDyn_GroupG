//
// Created by daniel on 27.01.22.
//

#ifndef PSEMOLDYN_GROUPG_CSVWRITER_H
#define PSEMOLDYN_GROUPG_CSVWRITER_H

#include <string>

class CSVWriter{

public:
    CSVWriter();
    ~CSVWriter();

    /**
     * @brief Appends a new line to an existing CSV-file
     * @param path the path of the CSV-file
     * @param line the new line which will be appended
     */
    void writeToFile(const std::string &path, const std::string &line);

    /**
     * @brief Creates a new CSV-file by overwriting existing files
     * @param path the path where the CSV-file should be created
     */
    void createCSV(const std::string &path);
};


#endif //PSEMOLDYN_GROUPG_CSVWRITER_H
