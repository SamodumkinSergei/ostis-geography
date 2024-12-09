/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace VitebskVillagesModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const question_largerVillageByPopulationInTheDistrict{"question_largerVillageByPopulationInTheDistrict", ScType::ConstNodeClass};

  static inline ScKeynode const question_largerVillageByPopulation{"question_largerVillageByPopulation", ScType::ConstNodeClass};

  static inline ScKeynode const question_greatestDistanceToTheRegionalCenter{"question_greatestDistanceToTheRegionalCenter", ScType::ConstNodeClass};

  static inline ScKeynode const nrel_population{"nrel_population", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_distanceFromArea{"nrel_distanceFromArea", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_district{"nrel_district", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};
};

}  // namespace VitebskVillagesModule
