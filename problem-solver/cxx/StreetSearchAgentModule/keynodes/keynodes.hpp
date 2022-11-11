#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace StreetSearchAgentModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:

  SC_PROPERTY(Keynode("action_streetByLenghtSearch"), ForceCreate)
  static ScAddr action_streetByLenghtSearch;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  SC_PROPERTY(Keynode("nrel_street_length"), ForceCreate)
  static ScAddr nrel_street_length;

  SC_PROPERTY(Keynode("nrel_search_area"), ForceCreate)
  static ScAddr nrel_search_area;
};

} // namespace exampleModule
