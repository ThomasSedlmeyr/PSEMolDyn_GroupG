//
// Created by thomas on 20.01.22.
//

#ifndef PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONANALYZER_H
#define PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONANALYZER_H


#include <vector>
#include "SimulationAnalysis/Analyzer.h"

class RadialPairDistributionAnalyzer : public Analyzer{
private:
    /**
     * @brief the start of the intervall which will be considered for the calculation
     */
    double startOfIntervall;

    /**
     * @brief the steps size of the intervalls which will be calculated
     */
    double stepSize;

    /**
     * @brief the steps size of the time steps for which the RDF will be calculated
     */
    int timeStepSize;

    /**
     * @brief the current time of the simulation
     */
    int currentTime = 0;

    /**
     * @brief
     */
    std::vector<int> numberParticlesInIntervall;

    /**
     * @brief the localDensities which store the results of the analysis
     */
    std::vector<double> localDensities;

    std::string calculationResultsToString() override;

public:
    /**
     * @brief The Constructor
     * @param particleContainer the container on which we operate on
     * @param startOfIntervall the start of the intervall which will be considered for the calculation
     * @param stepSize the step size of the intervalls
     * @param numberOfValues the number of distances
     * @param startTime the startTime of the analysis
     * @param timeStepSize the step size of the time
     */
    RadialPairDistributionAnalyzer(ParticleContainer *particleContainer,
                                   double startOfIntervall, double stepSize,
                                   int numberOfValues, int startTime, int timeStepSize);

    void calculateLocalDensities();

    ~RadialPairDistributionAnalyzer() override;

    const std::vector<double> &getLocalDensities() const;

    const std::vector<int> &getNumberParticlesInIntervall() const;

    std::string createHeaderLine() override;
};


#endif //PSEMOLDYN_GROUPG_RADIALPAIRDISTRIBUTIONANALYZER_H
