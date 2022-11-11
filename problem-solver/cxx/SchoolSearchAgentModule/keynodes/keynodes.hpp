#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace SchoolSearchAgentModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_schoolByNumberSearch"), ForceCreate)
  static ScAddr action_schoolByNumberSearch;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  SC_PROPERTY(Keynode("nrel_school_number"), ForceCreate)
  static ScAddr nrel_school_number;

  SC_PROPERTY(Keynode("nrel_search_area"), ForceCreate)
  static ScAddr nrel_search_area;
};

}  // namespace SchoolSearchAgentModule
