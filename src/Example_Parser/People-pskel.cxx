// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "People-pskel.hxx"

// person_pskel
//

void person_pskel::
first_name_parser(::xml_schema::string_pskel &p) {
    this->first_name_parser_ = &p;
}

void person_pskel::
last_name_parser(::xml_schema::string_pskel &p) {
    this->last_name_parser_ = &p;
}

void person_pskel::
gender_parser(::gender_pskel &p) {
    this->gender_parser_ = &p;
}

void person_pskel::
age_parser(::xml_schema::short_pskel &p) {
    this->age_parser_ = &p;
}

void person_pskel::
parsers(::xml_schema::string_pskel &first_name,
        ::xml_schema::string_pskel &last_name,
        ::gender_pskel &gender,
        ::xml_schema::short_pskel &age) {
    this->first_name_parser_ = &first_name;
    this->last_name_parser_ = &last_name;
    this->gender_parser_ = &gender;
    this->age_parser_ = &age;
}

person_pskel::
person_pskel()
        : first_name_parser_(0),
          last_name_parser_(0),
          gender_parser_(0),
          age_parser_(0) {
}

// people_pskel
//

void people_pskel::
person_parser(::person_pskel &p) {
    this->person_parser_ = &p;
}

void people_pskel::
parsers(::person_pskel &person) {
    this->person_parser_ = &person;
}

people_pskel::
people_pskel()
        : person_parser_(0) {
}

// gender_pskel
//

void gender_pskel::
post_gender() {
}

// person_pskel
//

void person_pskel::
first_name(const ::std::string &) {
}

void person_pskel::
last_name(const ::std::string &) {
}

void person_pskel::
gender() {
}

void person_pskel::
age(short) {
}

void person_pskel::
post_person() {
}

bool person_pskel::
_start_element_impl(const ::xml_schema::ro_string &ns,
                    const ::xml_schema::ro_string &n,
                    const ::xml_schema::ro_string *t) {
    XSD_UNUSED (t);

    if (this->::xml_schema::complex_content::_start_element_impl(ns, n, t))
        return true;

    if (n == "first-name" && ns.empty()) {
        this->::xml_schema::complex_content::context_.top().parser_ = this->first_name_parser_;

        if (this->first_name_parser_)
            this->first_name_parser_->pre();

        return true;
    }

    if (n == "last-name" && ns.empty()) {
        this->::xml_schema::complex_content::context_.top().parser_ = this->last_name_parser_;

        if (this->last_name_parser_)
            this->last_name_parser_->pre();

        return true;
    }

    if (n == "gender" && ns.empty()) {
        this->::xml_schema::complex_content::context_.top().parser_ = this->gender_parser_;

        if (this->gender_parser_)
            this->gender_parser_->pre();

        return true;
    }

    if (n == "age" && ns.empty()) {
        this->::xml_schema::complex_content::context_.top().parser_ = this->age_parser_;

        if (this->age_parser_)
            this->age_parser_->pre();

        return true;
    }

    return false;
}

bool person_pskel::
_end_element_impl(const ::xml_schema::ro_string &ns,
                  const ::xml_schema::ro_string &n) {
    if (this->::xml_schema::complex_content::_end_element_impl(ns, n))
        return true;

    if (n == "first-name" && ns.empty()) {
        if (this->first_name_parser_)
            this->first_name(this->first_name_parser_->post_string());

        return true;
    }

    if (n == "last-name" && ns.empty()) {
        if (this->last_name_parser_)
            this->last_name(this->last_name_parser_->post_string());

        return true;
    }

    if (n == "gender" && ns.empty()) {
        if (this->gender_parser_) {
            this->gender_parser_->post_gender();
            this->gender();
        }

        return true;
    }

    if (n == "age" && ns.empty()) {
        if (this->age_parser_)
            this->age(this->age_parser_->post_short());

        return true;
    }

    return false;
}

// people_pskel
//

void people_pskel::
person() {
}

void people_pskel::
post_people() {
}

bool people_pskel::
_start_element_impl(const ::xml_schema::ro_string &ns,
                    const ::xml_schema::ro_string &n,
                    const ::xml_schema::ro_string *t) {
    XSD_UNUSED (t);

    if (this->::xml_schema::complex_content::_start_element_impl(ns, n, t))
        return true;

    if (n == "person" && ns.empty()) {
        this->::xml_schema::complex_content::context_.top().parser_ = this->person_parser_;

        if (this->person_parser_)
            this->person_parser_->pre();

        return true;
    }

    return false;
}

bool people_pskel::
_end_element_impl(const ::xml_schema::ro_string &ns,
                  const ::xml_schema::ro_string &n) {
    if (this->::xml_schema::complex_content::_end_element_impl(ns, n))
        return true;

    if (n == "person" && ns.empty()) {
        if (this->person_parser_) {
            this->person_parser_->post_person();
            this->person();
        }

        return true;
    }

    return false;
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

