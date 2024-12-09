#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

namespace SearchFastestWayAgentModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_search_fastest_way{"action_search_fastest_way" , ScType::ConstNodeClass};
  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};

  static inline ScKeynode const concept_parameter{"concept_parameter", ScType::ConstNodeClass};
};

}  // namespace SearchFastestWayAgentModule
