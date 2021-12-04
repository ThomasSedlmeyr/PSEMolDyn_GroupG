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

#include "input-pskel.hxx"

// paramsLJ_pskel
//

void paramsLJ_pskel::
epsilon_parser (::xml_schema::double_pskel& p)
{
  this->epsilon_parser_ = &p;
}

void paramsLJ_pskel::
mass_parser (::xml_schema::double_pskel& p)
{
  this->mass_parser_ = &p;
}

void paramsLJ_pskel::
rho_parser (::xml_schema::double_pskel& p)
{
  this->rho_parser_ = &p;
}

void paramsLJ_pskel::
h_parser (::xml_schema::double_pskel& p)
{
  this->h_parser_ = &p;
}

void paramsLJ_pskel::
parsers (::xml_schema::double_pskel& epsilon,
         ::xml_schema::double_pskel& mass,
         ::xml_schema::double_pskel& rho,
         ::xml_schema::double_pskel& h)
{
  this->epsilon_parser_ = &epsilon;
  this->mass_parser_ = &mass;
  this->rho_parser_ = &rho;
  this->h_parser_ = &h;
}

paramsLJ_pskel::
paramsLJ_pskel ()
: epsilon_parser_ (0),
  mass_parser_ (0),
  rho_parser_ (0),
  h_parser_ (0)
{
}

// boundaryConditions_pskel
//

void boundaryConditions_pskel::
top_parser (::xml_schema::int_pskel& p)
{
  this->top_parser_ = &p;
}

void boundaryConditions_pskel::
right_parser (::xml_schema::int_pskel& p)
{
  this->right_parser_ = &p;
}

void boundaryConditions_pskel::
bottom_parser (::xml_schema::int_pskel& p)
{
  this->bottom_parser_ = &p;
}

void boundaryConditions_pskel::
left_parser (::xml_schema::int_pskel& p)
{
  this->left_parser_ = &p;
}

void boundaryConditions_pskel::
front_parser (::xml_schema::int_pskel& p)
{
  this->front_parser_ = &p;
}

void boundaryConditions_pskel::
back_parser (::xml_schema::int_pskel& p)
{
  this->back_parser_ = &p;
}

void boundaryConditions_pskel::
parsers (::xml_schema::int_pskel& top,
         ::xml_schema::int_pskel& right,
         ::xml_schema::int_pskel& bottom,
         ::xml_schema::int_pskel& left,
         ::xml_schema::int_pskel& front,
         ::xml_schema::int_pskel& back)
{
  this->top_parser_ = &top;
  this->right_parser_ = &right;
  this->bottom_parser_ = &bottom;
  this->left_parser_ = &left;
  this->front_parser_ = &front;
  this->back_parser_ = &back;
}

boundaryConditions_pskel::
boundaryConditions_pskel ()
: top_parser_ (0),
  right_parser_ (0),
  bottom_parser_ (0),
  left_parser_ (0),
  front_parser_ (0),
  back_parser_ (0)
{
}

// particlesLJ_pskel
//

void particlesLJ_pskel::
body_parser (::body_pskel& p)
{
  this->body_parser_ = &p;
}

void particlesLJ_pskel::
parsers (::body_pskel& body)
{
  this->body_parser_ = &body;
}

particlesLJ_pskel::
particlesLJ_pskel ()
: body_parser_ (0)
{
}

// input_pskel
//

void input_pskel::
t_end_parser (::xml_schema::double_pskel& p)
{
  this->t_end_parser_ = &p;
}

void input_pskel::
delta_t_parser (::xml_schema::double_pskel& p)
{
  this->delta_t_parser_ = &p;
}

void input_pskel::
calcType_parser (::xml_schema::string_pskel& p)
{
  this->calcType_parser_ = &p;
}

void input_pskel::
baseNameOutputFiles_parser (::xml_schema::string_pskel& p)
{
  this->baseNameOutputFiles_parser_ = &p;
}

void input_pskel::
writeFrequency_parser (::xml_schema::int_pskel& p)
{
  this->writeFrequency_parser_ = &p;
}

void input_pskel::
gravInput_parser (::xml_schema::string_pskel& p)
{
  this->gravInput_parser_ = &p;
}

void input_pskel::
paramsLJ_parser (::paramsLJ_pskel& p)
{
  this->paramsLJ_parser_ = &p;
}

void input_pskel::
boundaryConditions_parser (::boundaryConditions_pskel& p)
{
  this->boundaryConditions_parser_ = &p;
}

void input_pskel::
particlesLJ_parser (::particlesLJ_pskel& p)
{
  this->particlesLJ_parser_ = &p;
}

void input_pskel::
parsers (::xml_schema::double_pskel& t_end,
         ::xml_schema::double_pskel& delta_t,
         ::xml_schema::string_pskel& calcType,
         ::xml_schema::string_pskel& baseNameOutputFiles,
         ::xml_schema::int_pskel& writeFrequency,
         ::xml_schema::string_pskel& gravInput,
         ::paramsLJ_pskel& paramsLJ,
         ::boundaryConditions_pskel& boundaryConditions,
         ::particlesLJ_pskel& particlesLJ)
{
  this->t_end_parser_ = &t_end;
  this->delta_t_parser_ = &delta_t;
  this->calcType_parser_ = &calcType;
  this->baseNameOutputFiles_parser_ = &baseNameOutputFiles;
  this->writeFrequency_parser_ = &writeFrequency;
  this->gravInput_parser_ = &gravInput;
  this->paramsLJ_parser_ = &paramsLJ;
  this->boundaryConditions_parser_ = &boundaryConditions;
  this->particlesLJ_parser_ = &particlesLJ;
}

input_pskel::
input_pskel ()
: t_end_parser_ (0),
  delta_t_parser_ (0),
  calcType_parser_ (0),
  baseNameOutputFiles_parser_ (0),
  writeFrequency_parser_ (0),
  gravInput_parser_ (0),
  paramsLJ_parser_ (0),
  boundaryConditions_parser_ (0),
  particlesLJ_parser_ (0)
{
}

// body_pskel
//

void body_pskel::
bodyType_parser (::xml_schema::string_pskel& p)
{
  this->bodyType_parser_ = &p;
}

void body_pskel::
position_parser (::xml_schema::string_pskel& p)
{
  this->position_parser_ = &p;
}

void body_pskel::
velocity_parser (::xml_schema::string_pskel& p)
{
  this->velocity_parser_ = &p;
}

void body_pskel::
objectSpecificFormat_parser (::xml_schema::string_pskel& p)
{
  this->objectSpecificFormat_parser_ = &p;
}

void body_pskel::
parsers (::xml_schema::string_pskel& bodyType,
         ::xml_schema::string_pskel& position,
         ::xml_schema::string_pskel& velocity,
         ::xml_schema::string_pskel& objectSpecificFormat)
{
  this->bodyType_parser_ = &bodyType;
  this->position_parser_ = &position;
  this->velocity_parser_ = &velocity;
  this->objectSpecificFormat_parser_ = &objectSpecificFormat;
}

body_pskel::
body_pskel ()
: bodyType_parser_ (0),
  position_parser_ (0),
  velocity_parser_ (0),
  objectSpecificFormat_parser_ (0)
{
}

// paramsLJ_pskel
//

void paramsLJ_pskel::
epsilon (double)
{
}

void paramsLJ_pskel::
mass (double)
{
}

void paramsLJ_pskel::
rho (double)
{
}

void paramsLJ_pskel::
h (double)
{
}

bool paramsLJ_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  if (this->::xml_schema::complex_content::_start_element_impl (ns, n, t))
    return true;

  if (n == "epsilon" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->epsilon_parser_;

    if (this->epsilon_parser_)
      this->epsilon_parser_->pre ();

    return true;
  }

  if (n == "mass" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->mass_parser_;

    if (this->mass_parser_)
      this->mass_parser_->pre ();

    return true;
  }

  if (n == "rho" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->rho_parser_;

    if (this->rho_parser_)
      this->rho_parser_->pre ();

    return true;
  }

  if (n == "h" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->h_parser_;

    if (this->h_parser_)
      this->h_parser_->pre ();

    return true;
  }

  return false;
}

bool paramsLJ_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  if (this->::xml_schema::complex_content::_end_element_impl (ns, n))
    return true;

  if (n == "epsilon" && ns.empty ())
  {
    if (this->epsilon_parser_)
      this->epsilon (this->epsilon_parser_->post_double ());

    return true;
  }

  if (n == "mass" && ns.empty ())
  {
    if (this->mass_parser_)
      this->mass (this->mass_parser_->post_double ());

    return true;
  }

  if (n == "rho" && ns.empty ())
  {
    if (this->rho_parser_)
      this->rho (this->rho_parser_->post_double ());

    return true;
  }

  if (n == "h" && ns.empty ())
  {
    if (this->h_parser_)
      this->h (this->h_parser_->post_double ());

    return true;
  }

  return false;
}

// boundaryConditions_pskel
//

void boundaryConditions_pskel::
top (int)
{
}

void boundaryConditions_pskel::
right (int)
{
}

void boundaryConditions_pskel::
bottom (int)
{
}

void boundaryConditions_pskel::
left (int)
{
}

void boundaryConditions_pskel::
front (int)
{
}

void boundaryConditions_pskel::
back (int)
{
}

bool boundaryConditions_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  if (this->::xml_schema::complex_content::_start_element_impl (ns, n, t))
    return true;

  if (n == "top" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->top_parser_;

    if (this->top_parser_)
      this->top_parser_->pre ();

    return true;
  }

  if (n == "right" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->right_parser_;

    if (this->right_parser_)
      this->right_parser_->pre ();

    return true;
  }

  if (n == "bottom" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->bottom_parser_;

    if (this->bottom_parser_)
      this->bottom_parser_->pre ();

    return true;
  }

  if (n == "left" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->left_parser_;

    if (this->left_parser_)
      this->left_parser_->pre ();

    return true;
  }

  if (n == "front" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->front_parser_;

    if (this->front_parser_)
      this->front_parser_->pre ();

    return true;
  }

  if (n == "back" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->back_parser_;

    if (this->back_parser_)
      this->back_parser_->pre ();

    return true;
  }

  return false;
}

bool boundaryConditions_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  if (this->::xml_schema::complex_content::_end_element_impl (ns, n))
    return true;

  if (n == "top" && ns.empty ())
  {
    if (this->top_parser_)
      this->top (this->top_parser_->post_int ());

    return true;
  }

  if (n == "right" && ns.empty ())
  {
    if (this->right_parser_)
      this->right (this->right_parser_->post_int ());

    return true;
  }

  if (n == "bottom" && ns.empty ())
  {
    if (this->bottom_parser_)
      this->bottom (this->bottom_parser_->post_int ());

    return true;
  }

  if (n == "left" && ns.empty ())
  {
    if (this->left_parser_)
      this->left (this->left_parser_->post_int ());

    return true;
  }

  if (n == "front" && ns.empty ())
  {
    if (this->front_parser_)
      this->front (this->front_parser_->post_int ());

    return true;
  }

  if (n == "back" && ns.empty ())
  {
    if (this->back_parser_)
      this->back (this->back_parser_->post_int ());

    return true;
  }

  return false;
}

// particlesLJ_pskel
//

void particlesLJ_pskel::
body (const ::body&)
{
}

bool particlesLJ_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  if (this->::xml_schema::complex_content::_start_element_impl (ns, n, t))
    return true;

  if (n == "body" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->body_parser_;

    if (this->body_parser_)
      this->body_parser_->pre ();

    return true;
  }

  return false;
}

bool particlesLJ_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  if (this->::xml_schema::complex_content::_end_element_impl (ns, n))
    return true;

  if (n == "body" && ns.empty ())
  {
    if (this->body_parser_)
      this->body (this->body_parser_->post_body ());

    return true;
  }

  return false;
}

// input_pskel
//

void input_pskel::
t_end (double)
{
}

void input_pskel::
delta_t (double)
{
}

void input_pskel::
calcType (const ::std::string&)
{
}

void input_pskel::
baseNameOutputFiles (const ::std::string&)
{
}

void input_pskel::
writeFrequency (int)
{
}

void input_pskel::
gravInput (const ::std::string&)
{
}

void input_pskel::
paramsLJ (const ::paramsLJ&)
{
}

void input_pskel::
boundaryConditions (const ::boundaryConditions&)
{
}

void input_pskel::
particlesLJ (const ::particlesLJ&)
{
}

bool input_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  if (this->::xml_schema::complex_content::_start_element_impl (ns, n, t))
    return true;

  if (n == "t_end" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->t_end_parser_;

    if (this->t_end_parser_)
      this->t_end_parser_->pre ();

    return true;
  }

  if (n == "delta_t" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->delta_t_parser_;

    if (this->delta_t_parser_)
      this->delta_t_parser_->pre ();

    return true;
  }

  if (n == "calcType" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->calcType_parser_;

    if (this->calcType_parser_)
      this->calcType_parser_->pre ();

    return true;
  }

  if (n == "baseNameOutputFiles" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->baseNameOutputFiles_parser_;

    if (this->baseNameOutputFiles_parser_)
      this->baseNameOutputFiles_parser_->pre ();

    return true;
  }

  if (n == "writeFrequency" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->writeFrequency_parser_;

    if (this->writeFrequency_parser_)
      this->writeFrequency_parser_->pre ();

    return true;
  }

  if (n == "gravInput" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->gravInput_parser_;

    if (this->gravInput_parser_)
      this->gravInput_parser_->pre ();

    return true;
  }

  if (n == "paramsLJ" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->paramsLJ_parser_;

    if (this->paramsLJ_parser_)
      this->paramsLJ_parser_->pre ();

    return true;
  }

  if (n == "boundaryConditions" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->boundaryConditions_parser_;

    if (this->boundaryConditions_parser_)
      this->boundaryConditions_parser_->pre ();

    return true;
  }

  if (n == "particlesLJ" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->particlesLJ_parser_;

    if (this->particlesLJ_parser_)
      this->particlesLJ_parser_->pre ();

    return true;
  }

  return false;
}

bool input_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  if (this->::xml_schema::complex_content::_end_element_impl (ns, n))
    return true;

  if (n == "t_end" && ns.empty ())
  {
    if (this->t_end_parser_)
      this->t_end (this->t_end_parser_->post_double ());

    return true;
  }

  if (n == "delta_t" && ns.empty ())
  {
    if (this->delta_t_parser_)
      this->delta_t (this->delta_t_parser_->post_double ());

    return true;
  }

  if (n == "calcType" && ns.empty ())
  {
    if (this->calcType_parser_)
      this->calcType (this->calcType_parser_->post_string ());

    return true;
  }

  if (n == "baseNameOutputFiles" && ns.empty ())
  {
    if (this->baseNameOutputFiles_parser_)
      this->baseNameOutputFiles (this->baseNameOutputFiles_parser_->post_string ());

    return true;
  }

  if (n == "writeFrequency" && ns.empty ())
  {
    if (this->writeFrequency_parser_)
      this->writeFrequency (this->writeFrequency_parser_->post_int ());

    return true;
  }

  if (n == "gravInput" && ns.empty ())
  {
    if (this->gravInput_parser_)
      this->gravInput (this->gravInput_parser_->post_string ());

    return true;
  }

  if (n == "paramsLJ" && ns.empty ())
  {
    if (this->paramsLJ_parser_)
      this->paramsLJ (this->paramsLJ_parser_->post_paramsLJ ());

    return true;
  }

  if (n == "boundaryConditions" && ns.empty ())
  {
    if (this->boundaryConditions_parser_)
      this->boundaryConditions (this->boundaryConditions_parser_->post_boundaryConditions ());

    return true;
  }

  if (n == "particlesLJ" && ns.empty ())
  {
    if (this->particlesLJ_parser_)
      this->particlesLJ (this->particlesLJ_parser_->post_particlesLJ ());

    return true;
  }

  return false;
}

// body_pskel
//

void body_pskel::
bodyType (const ::std::string&)
{
}

void body_pskel::
position (const ::std::string&)
{
}

void body_pskel::
velocity (const ::std::string&)
{
}

void body_pskel::
objectSpecificFormat (const ::std::string&)
{
}

bool body_pskel::
_start_element_impl (const ::xml_schema::ro_string& ns,
                     const ::xml_schema::ro_string& n,
                     const ::xml_schema::ro_string* t)
{
  XSD_UNUSED (t);

  if (this->::xml_schema::complex_content::_start_element_impl (ns, n, t))
    return true;

  if (n == "bodyType" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->bodyType_parser_;

    if (this->bodyType_parser_)
      this->bodyType_parser_->pre ();

    return true;
  }

  if (n == "position" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->position_parser_;

    if (this->position_parser_)
      this->position_parser_->pre ();

    return true;
  }

  if (n == "velocity" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->velocity_parser_;

    if (this->velocity_parser_)
      this->velocity_parser_->pre ();

    return true;
  }

  if (n == "objectSpecificFormat" && ns.empty ())
  {
    this->::xml_schema::complex_content::context_.top ().parser_ = this->objectSpecificFormat_parser_;

    if (this->objectSpecificFormat_parser_)
      this->objectSpecificFormat_parser_->pre ();

    return true;
  }

  return false;
}

bool body_pskel::
_end_element_impl (const ::xml_schema::ro_string& ns,
                   const ::xml_schema::ro_string& n)
{
  if (this->::xml_schema::complex_content::_end_element_impl (ns, n))
    return true;

  if (n == "bodyType" && ns.empty ())
  {
    if (this->bodyType_parser_)
      this->bodyType (this->bodyType_parser_->post_string ());

    return true;
  }

  if (n == "position" && ns.empty ())
  {
    if (this->position_parser_)
      this->position (this->position_parser_->post_string ());

    return true;
  }

  if (n == "velocity" && ns.empty ())
  {
    if (this->velocity_parser_)
      this->velocity (this->velocity_parser_->post_string ());

    return true;
  }

  if (n == "objectSpecificFormat" && ns.empty ())
  {
    if (this->objectSpecificFormat_parser_)
      this->objectSpecificFormat (this->objectSpecificFormat_parser_->post_string ());

    return true;
  }

  return false;
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

