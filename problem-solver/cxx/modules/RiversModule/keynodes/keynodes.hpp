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

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const question_theBiggestBasinInRegion{"question_theBiggestBasinInRegion"};

  static inline ScKeynode const question_longerRiver{"question_longerRiver"};

  static inline ScKeynode const question_shorterRiver{"question_shorterRiver"};

  static inline ScKeynode const question_biggerBasin{"question_biggerBasin"};

  static inline ScKeynode const question_longestInRegion{"question_longestInRegion"};

  static inline ScKeynode const nrel_length{"nrel_length"};

  static inline ScKeynode const nrel_basin{"nrel_basin"};

  static inline ScKeynode const nrel_region{"nrel_region"};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf"};
};

}  // namespace RiversModule
