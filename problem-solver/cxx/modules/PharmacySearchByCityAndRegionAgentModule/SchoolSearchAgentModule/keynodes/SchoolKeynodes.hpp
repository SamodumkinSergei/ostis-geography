#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

namespace SchoolSearchAgentModule
{

class SchoolKeynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_schoolByNumberSearch{"action_schoolByNumberSearch"};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf"};

  static inline ScKeynode const nrel_school_number{"nrel_school_number"};

  static inline ScKeynode const nrel_search_area{"nrel_search_area"};

  // static inline ScKeynode const concept_school_request("concept_school_request");
};

}  // namespace SchoolSearchAgentModule
