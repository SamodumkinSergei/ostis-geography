/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace RiversModule
{

class RiverKeynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_get_theBiggestBasinInRegion{"action_get_theBiggestBasinInRegion"};

  static inline ScKeynode const action_get_longerRiver{"action_get_longerRiver"};

  static inline ScKeynode const action_get_shorterRiver{"action_get_shorterRiver"};

  static inline ScKeynode const action_get_biggerBasin{"action_get_biggerBasin"};

  static inline ScKeynode const action_get_longestInRegion{"action_get_longestInRegion"};

  static inline ScKeynode const nrel_length{"nrel_length"};

  static inline ScKeynode const nrel_basin{"nrel_basin"};

  static inline ScKeynode const nrel_region{"nrel_region"};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf"};

  // static inline ScKeynode const concept_river_request("concept_river_request");
};

}  // namespace RiversModule
