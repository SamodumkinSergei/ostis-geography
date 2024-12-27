#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

namespace PharmacySearchByCityAndRegionAgentModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_pharmacyByCityAndRegionSearch1{"action_pharmacyByCityAndRegionSearch1", ScType::NodeConstClass};

  static inline ScKeynode const action_pharmacyByCityAndRegionSearch{"action_pharmacyByCityAndRegionSearch"};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf"};

  static inline ScKeynode const nrel_city{"nrel_city"};

  static inline ScKeynode const nrel_region{"nrel_region"};
};

}  // namespace PharmacySearchByCityAndRegionAgentModule
