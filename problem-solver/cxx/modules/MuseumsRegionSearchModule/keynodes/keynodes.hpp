/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>
#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace MuseumsRegionSearchModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_museumsRegionSearch{"action_museumsRegionSearch"};

  static inline ScKeynode const nrel_region{"nrel_region"};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf"};

  static inline ScKeynode const concept_museum{"concept_museum"};
};

}  // namespace MuseumsRegionSearchModule
