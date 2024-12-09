/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace VillagesModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const question_vitebskVillage{"question_vitebskVillage", ScType::ConstNodeClass};

  static inline ScKeynode const nrel_length{"nrel_length", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};
};

}  // namespace VillagesModule
