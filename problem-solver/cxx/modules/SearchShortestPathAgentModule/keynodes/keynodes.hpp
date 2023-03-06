#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace SearchShortestPathAgentModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_search_min_path"), ForceCreate)
  static ScAddr action_search_min_path;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  SC_PROPERTY(Keynode("concept_parameter"), ForceCreate)
  static ScAddr concept_parameter;

  SC_PROPERTY(Keynode("nrel_bordering_points"), ForceCreate)
  static ScAddr nrel_bordering_points;

  SC_PROPERTY(Keynode("concept_length"), ForceCreate)
  static ScAddr concept_length;

  SC_PROPERTY(Keynode("concept_crossroad"), ForceCreate)
  static ScAddr concept_crossroad;

  SC_PROPERTY(Keynode("concept_road"), ForceCreate)
  static ScAddr concept_road;
};

}
