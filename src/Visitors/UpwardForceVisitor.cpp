//
// Created by philip on 16.12.21.
//

#include "UpwardForceVisitor.h"
#include <spdlog/spdlog.h>

std::vector<int> UpwardForceVisitor::particlesWithFZUp{};
double UpwardForceVisitor::fZUp = 0.8;

void UpwardForceVisitor::visitParticle(Particle &p) {
    if (std::find(particlesWithFZUp.begin(), particlesWithFZUp.end(), p.getId()) != particlesWithFZUp.end()){
        auto &fRef = p.getFRef();
        fRef[2] += fZUp;
        //spdlog::info("Applied FZUp to Particle with ID " + std::to_string(p.getId()) + "\n");
    }
}