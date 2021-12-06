//
// Created by thomas on 06.12.21.
//

#ifndef PSEMOLDYN_GROUPG_PERSON_PIPMPL_H
#define PSEMOLDYN_GROUPG_PERSON_PIPMPL_H

#include "People-pskel.hxx"

class person_pimpl : public person_pskel {
public:
    virtual void first_name(const std::string &n);

    virtual void last_name(const std::string &l);

    virtual void age(short a);
};

#endif //PSEMOLDYN_GROUPG_PERSON_PIPMPL_H
