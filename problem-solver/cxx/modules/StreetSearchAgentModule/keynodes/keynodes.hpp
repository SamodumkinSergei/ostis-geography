#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

namespace StreetSearchAgentModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_streetByLenghtSearch{"action_streetByLenghtSearch", ScType::ConstNodeClass};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_street_length{"nrel_street_length", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_search_area{"nrel_search_area", ScType::ConstNodeNonRole};
};

}  // namespace StreetSearchAgentModule
