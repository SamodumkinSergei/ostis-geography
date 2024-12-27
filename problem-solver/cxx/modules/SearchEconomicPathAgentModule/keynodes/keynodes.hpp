#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

namespace SearchEconomicPathAgentModule
{
// Класс Keynodes содержит определения для ключевых узлов, используемых в проекте
class Keynodes : public ScKeynodes
{
  public:
  // Ключевые узлы для разных вопросов
  static inline ScKeynode const action_search_economic_path{"action_search_economic_path", ScType::ConstNodeClass};
  // Ключевые узлы для различных типов отношений
  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};

  static inline ScKeynode const concept_parameter{"concept_parameter", ScType::ConstNodeClass};
};

}  // namespace SearchEconomicPathAgentModule
