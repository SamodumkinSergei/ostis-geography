#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace SearchCostToBaranovichiAgentModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_search_how_much_cost_to_go_to_Baranovichi"), ForceCreate)
  static ScAddr action_search_how_much_cost_to_go_to_Baranovichi;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  SC_PROPERTY(Keynode("concept_parameter"), ForceCreate)
  static ScAddr concept_parameter;
};

}  // namespace SearchCostToBaranovichiAgentModule
