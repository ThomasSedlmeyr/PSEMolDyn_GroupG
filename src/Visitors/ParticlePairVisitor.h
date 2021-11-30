//
// Created by philip on 29.11.21.
//

#ifndef PSEMOLDYN_GROUPG_PARTICLEPAIRVISITOR_H
#define PSEMOLDYN_GROUPG_PARTICLEPAIRVISITOR_H


class ParticlePairVisitor {
public:
    virtual void visitParticlePair(Particle &p1, Particle &p2) = 0;
};


#endif //PSEMOLDYN_GROUPG_PARTICLEPAIRVISITOR_H
