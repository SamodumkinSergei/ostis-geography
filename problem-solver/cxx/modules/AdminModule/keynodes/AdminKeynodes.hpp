#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace adminModule
{

class AdminKeynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_get_embassy{"action_get_embassy"};

  static inline ScKeynode const action_get_admin_building_district{"action_get_admin_building_district"};

  static inline ScKeynode const concept_admin_building{"concept_admin_building"};

  static inline ScKeynode const concept_admin_building_request{"concept_admin_building_request"};

  static inline ScKeynode const action_get_admin_building_region{"action_get_admin_building_region"};

  static inline ScKeynode const nrel_region{"nrel_region"};

  static inline ScKeynode const nrel_embassy{"nrel_embassy"};

  static inline ScKeynode const nrel_search_area{"nrel_search_area"};

  static inline ScKeynode const minsk{"minsk"};
};

}  
