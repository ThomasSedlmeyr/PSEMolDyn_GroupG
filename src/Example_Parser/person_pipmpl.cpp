//
// Created by thomas on 06.12.21.
//
#include <iostream>
#include "person_pipmpl.h"

void person_pimpl::first_name(const std::string &n) {
    std::cout << "first : " << n << std::endl;
}

void person_pimpl::last_name(const std::string &l) {
    std::cout << "last: " << l << std::endl;
}

void person_pimpl::age(short a) {
    std::cout << "Age: " << a << std::endl;
}

