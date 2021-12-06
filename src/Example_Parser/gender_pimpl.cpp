//
// Created by thomas on 06.12.21.
//

#include <iostream>
#include "gender_pimpl.h"

void gender_pimpl::post_gender() {
    std::string s = post_string ();
    std::cout << "gender: " << s << std::endl;
}