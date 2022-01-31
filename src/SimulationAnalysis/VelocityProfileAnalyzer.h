//
// Created by thomas on 04.01.22.
//

#ifndef PSEMOLDYN_GROUPG_VELOCITYPROFILEANALYZER_H
#define PSEMOLDYN_GROUPG_VELOCITYPROFILEANALYZER_H


#include <array>
#include "Bin.h"
#include "XML_Parser/XMLParser.h"
#include "ParticleContainers/ParticleContainer.h"
#include "Analyzer.h"

class VelocityProfileAnalyzer : public Analyzer{

private:

    /**
     * @brief bins of domain
     */
    std::vector<Bin*> bins;

    /**
     * @brief width of individual bins
     */
    double binWidth;

public:
    /**
     * @brief calculate velocity and density profile
     */
    void calculateVelocityAndDensityProfile();

    explicit VelocityProfileAnalyzer(ParticleContainer *particleContainer);

    ~VelocityProfileAnalyzer() override;

    std::string calculationResultsToString() override;

    std::string createHeaderLine();
};


#endif //PSEMOLDYN_GROUPG_VELOCITYPROFILEANALYZER_H
