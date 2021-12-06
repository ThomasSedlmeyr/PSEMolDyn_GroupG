#include <iostream>
#include "people.h"

using namespace std;

int
main ()
{
    try {
        std::unique_ptr<people_t> ppl(people("people.xml"));

        // Iterate over individual person records.
        //
        people_t::person_sequence &ps(ppl->person());

        for (people_t::person_iterator i(ps.begin()); i != ps.end(); ++i) {
            person_t &p(*i);

            // Print names: first-name and last-name are required elements,
            // middle-name is optional.
            //
            cout << "name:   " << p.first_name() << " ";

            if (p.middle_name().present())
                cout << p.middle_name().get() << " ";

            cout << p.last_name() << endl;

            // Print gender, age, and id which are all required.
            //
            cout << "gender: " << p.gender() << endl
                 << "age:    " << p.age() << endl
                 << "id:     " << p.id() << endl
                 << endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << endl;
    }
}