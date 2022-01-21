#include "Bin.h"
#include <math.h>
#include "../XML_Parser/XMLParser.h"

void Bin::calculateDensity() {
    density = particles.size() / ((XMLParser::domainSize[0] / XMLParser::numberOfBins_p) * XMLParser::domainSize[1] * XMLParser::domainSize[2]);
}

void Bin::calculateVelocity() {
    double v = 0;
    for (Particle particle : particles) {
        v += particle.getV()[1];
    }
    v /= particles.size();
    meanVelocity = v;
}

double Bin::getDensity() const {
    return density;
}

double Bin::getMeanVelocity() const {
    return meanVelocity;
}

void Bin::setParticles(std::vector<Particle> particles_) {
    particles = particles_;
}
