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

// Класс Keynodes содержит определения для ключевых узлов, используемых в проекте
class Keynodes : public ScKeynodes
{
  public:
    // Ключевые узлы для разных вопросов
    static inline ScKeynode const question_largerVillageByPopulationInTheDistrict{"question_largerVillageByPopulationInTheDistrict", ScType::ConstNodeClass};
    static inline ScKeynode const question_largerVillageByPopulation{"question_largerVillageByPopulation", ScType::ConstNodeClass};
    static inline ScKeynode const question_greatestDistanceToTheRegionalCenter{"question_greatestDistanceToTheRegionalCenter", ScType::ConstNodeClass};

    // Ключевые узлы для различных типов отношений
    static inline ScKeynode const nrel_population{"nrel_population", ScType::ConstNodeNonRole}; // Население
    static inline ScKeynode const nrel_distanceFromArea{"nrel_distanceFromArea", ScType::ConstNodeNonRole}; // Расстояние от района
    static inline ScKeynode const nrel_district{"nrel_district", ScType::ConstNodeNonRole}; // Район
    static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole}; // Основное наименование
};

}  // namespace VitebskVillagesModule

