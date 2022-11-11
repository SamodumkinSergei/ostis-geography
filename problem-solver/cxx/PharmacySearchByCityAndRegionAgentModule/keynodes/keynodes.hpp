#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace PharmacySearchByCityAndRegionAgentModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:

  SC_PROPERTY(Keynode("action_pharmacyByCityAndRegionSearch"), ForceCreate)
  static ScAddr action_pharmacyByCityAndRegionSearch;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  SC_PROPERTY(Keynode("nrel_city"), ForceCreate)
  static ScAddr nrel_city;

  SC_PROPERTY(Keynode("nrel_region"), ForceCreate)
  static ScAddr nrel_region;
};

} // namespace exampleModule
