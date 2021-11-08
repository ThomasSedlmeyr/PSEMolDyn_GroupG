//
// Created by thomas on 07.11.21.
//

#include <vector>
#include <SimulationLogic/Particle.h>
#include <SimulationLogic/Simulation.h>
#include "ForceTester.h"

/*
bool ForceTester :: testOptimizedFormula(Simulation simulation){
    bool isCorrect = true;
    for (int i = 0; i < 1000; ++i) {
        //Store the original configuration
        std::vector<Particle> particlesOriginal = simulation.getParticleContainer().getParticles();
        //calculate the new force on particles with optimized Method
        simulation.calculateF();
        //store result for comparison with slower implementation
        std::vector<Particle> resultFast = particles;
        //reset particles to original state
        particles = particlesOriginal;
        calculateFslower();
        //Now compare particles with resultFast
        for (std::size_t j = 0; j < particles.size(); ++j) {
            if (!(particles[j] == resultFast[j])) {
                std::cout << "Error in Fast Calculation\n";
                isCorrect = false;
            }
        }
        calculateX(0.014);
        calculateV(0.014);
    }
    return isCorrect;
}
*/
