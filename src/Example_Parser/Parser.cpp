//
// Created by thomas on 06.12.21.
//

#include <iostream>
#include "Parser.h"

void Parser::main() {
    std::cout << "test\n";
    person_p.parsers(string_p, string_p, gender_p, short_p);
    people_p.parsers(person_p);

    xml_schema::document doc_p(people_p, "People");

    people_p.pre();
    doc_p.parse("People.xml");
    people_p.post_people();
}