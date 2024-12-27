/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>
#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace StatusAndDistrictSearchModule
{
// Класс Keynodes содержит определения для ключевых узлов, используемых в проекте
class Keynodes : public ScKeynodes
{
  public:
  // Ключевые узлы для разных вопросов
  static inline ScKeynode const action_statusAndDistrictSearch{"action_statusAndDistrictSearch", ScType::ConstNodeClass};

// Ключевые узлы для различных типов отношений
  static inline ScKeynode const nrel_district{"nrel_district", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_search_area{"nrel_search_area", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_city{"nrel_city", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_status{"nrel_status", ScType::ConstNodeNonRole};
};

}  // namespace StatusAndDistrictSearchModule
