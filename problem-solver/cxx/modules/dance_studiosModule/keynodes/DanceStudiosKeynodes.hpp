/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_addr.hpp>
#include <sc-memory/sc_object.hpp>

namespace dance_studios
{

class DanceStudiosKeynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_search_dance_studios_by_city{"action_search_dance_studios_by_city"};

  static inline ScKeynode const action_search_dance_studios_by_founding_year{"action_search_dance_studios_by_founding_year"};

  static inline ScKeynode const action_search_dance_studios_by_type{"action_search_dance_studios_by_type"};

  static inline ScKeynode const concept_solution{"concept_solution"};

  static inline ScKeynode const concept_success_solution{"concept_success_solution"};

  static inline ScKeynode const concept_city{"concept_city"};

  static inline ScKeynode const concept_year_of_foundation{"concept_year_of_foundation"};

  static inline ScKeynode const concept_type{"concept_type"};

  static inline ScKeynode const concept_dance_studio_request{"concept_dance_studio_request"};

  static inline ScKeynode const nrel_city{"nrel_city"};

  static inline ScKeynode const nrel_year_of_foundation{"nrel_year_of_foundation"};

  static inline ScKeynode const nrel_type{"nrel_type"};

  static inline ScKeynode const concept_dance_studio{"concept_dance_studio"};
};

}  
