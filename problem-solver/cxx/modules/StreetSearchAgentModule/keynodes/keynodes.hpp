#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

namespace StreetSearchAgentModule
{
  
// Класс Keynodes содержит определения для ключевых узлов, используемых в проекте
class Keynodes : public ScKeynodes
{
  public:
  // Ключевые узлы для разных вопросов
  static inline ScKeynode const action_streetByLenghtSearch{"action_streetByLenghtSearch", ScType::ConstNodeClass};

// Ключевые узлы для различных типов отношений
  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_street_length{"nrel_street_length", ScType::ConstNodeNonRole};

  static inline ScKeynode const nrel_search_area{"nrel_search_area", ScType::ConstNodeNonRole};
};

}  // namespace StreetSearchAgentModule
