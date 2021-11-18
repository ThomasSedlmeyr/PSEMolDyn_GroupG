#ifndef PSEMOLDYN_GROUPG_ARGUMENTCONTAINER_H
#define PSEMOLDYN_GROUPG_ARGUMENTCONTAINER_H

#include <vector>
#include <string>
#include <tuple>
class ArgumentContainer {

private:
    /**
     *@brief Stores the parameters with their specific values
     */
    std::vector<std::tuple<std::string, double>> paramsAndValues;

    /**
     * @brief prints error message when parameter file is faulty
     */
    void printErrorMessage();

public:
    /**
     * @brief Initializes paramsAndValues with the values which are stored in the file
     * @param filename the path to the file which contains the params and values
     * @return if the file could be read without any errors
     */
    bool readParamsAndValues(const std::string& filename);

    /**
     * @brief Checks if there is one entry in paramsAndValues for every parameter in params
     * @param params contains the parameters which should be contained in paramsAndValues
     * @return true if an entry with doubleValue exists. If not then false
     */
    bool checkIfParamsMatchParamsAndValues(std::vector<std::string> params);

    /**
     * @brief returns the value for a specific parameter
     * @param param the name of the parameter
     * @return the value of the parameter
     */
    double getValueToParam(const std::string& param);
};


#endif //PSEMOLDYN_GROUPG_ARGUMENTCONTAINER_H
