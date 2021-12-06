//
// Created by thomas on 06.12.21.
//

#ifndef PSEMOLDYN_GROUPG_GENDER_PIMPL_H
#define PSEMOLDYN_GROUPG_GENDER_PIMPL_H
#include "People-pskel.hxx"

class gender_pimpl: public gender_pskel,
                    public xml_schema::string_pimpl
{
public:
    void post_gender () override;

};


#endif //PSEMOLDYN_GROUPG_GENDER_PIMPL_H