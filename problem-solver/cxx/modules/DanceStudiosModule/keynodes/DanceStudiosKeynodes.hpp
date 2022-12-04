/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <sc-memory/sc_addr.hpp>
#include <sc-memory/sc_object.hpp>

#include "DanceStudiosKeynodes.generated.hpp"

namespace dance_studios
{

class DanceStudiosKeynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_search_dance_studios_by_city"), ForceCreate)
  static ScAddr action_search_dance_studios_by_city;

  SC_PROPERTY(Keynode("action_search_dance_studios_by_founding_year"), ForceCreate)
  static ScAddr action_search_dance_studios_by_founding_year;

  SC_PROPERTY(Keynode("action_search_dance_studios_by_style"), ForceCreate)
  static ScAddr action_search_dance_studios_by_style;

  SC_PROPERTY(Keynode("concept_solution"), ForceCreate)
  static ScAddr concept_solution;

  SC_PROPERTY(Keynode("concept_success_solution"), ForceCreate)
  static ScAddr concept_success_solution;

  SC_PROPERTY(Keynode("concept_city"), ForceCreate)
  static ScAddr concept_city;

  SC_PROPERTY(Keynode("concept_year_of_foundation"), ForceCreate)
  static ScAddr concept_year_of_foundation;

  SC_PROPERTY(Keynode("concept_dance_style"), ForceCreate)
  static ScAddr concept_dance_style;

  SC_PROPERTY(Keynode("nrel_city"), ForceCreate)
  static ScAddr nrel_city;

  SC_PROPERTY(Keynode("nrel_dance_studio_year_of_foundation"), ForceCreate)
  static ScAddr nrel_dance_studio_year_of_foundation;

  SC_PROPERTY(Keynode("nrel_dance_studio_style"), ForceCreate)
  static ScAddr nrel_dance_studio_style;

  SC_PROPERTY(Keynode("concept_dance_studio"), ForceCreate)
  static ScAddr concept_dance_studio;
};

}  // namespace dance_studios
