//
// Created by thomas on 06.12.21.
//

#ifndef PSEMOLDYN_GROUPG_PARSER_H
#define PSEMOLDYN_GROUPG_PARSER_H

#include "gender_pimpl.h"
#include "person_pipmpl.h"
#include "people_pimpl.h"


class Parser {
    xml_schema::short_pimpl short_p;
    xml_schema::string_pimpl string_p;

    gender_pimpl gender_p;
    person_pimpl person_p;
    people_pimpl people_p;


public:
    void main();
};


#endif //PSEMOLDYN_GROUPG_PARSER_H
