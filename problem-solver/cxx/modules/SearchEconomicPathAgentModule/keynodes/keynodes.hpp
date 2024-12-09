#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

namespace SearchEconomicPathAgentModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_search_economic_path{"action_search_economic_path", ScType::ConstNodeClass};
  
  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};

  static inline ScKeynode const concept_parameter{"concept_parameter", ScType::ConstNodeClass};
};

}  // namespace SearchEconomicPathAgentModule
