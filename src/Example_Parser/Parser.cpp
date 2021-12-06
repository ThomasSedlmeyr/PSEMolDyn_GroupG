//
// Created by thomas on 06.12.21.
//

#include "Parser.h"

void Parser::main() {
    person_p.parsers(string_p, string_p, gender_p, short_p);
    people_p.parsers(person_p);

    xml_schema::document doc_p(people_p, "people");

    people_p.pre();
    doc_p.parse("people.xml");
    people_p.post_people();
}