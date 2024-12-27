#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace soatoClassificationModule
{
// Класс Keynodes содержит определения для ключевых узлов, используемых в проекте
class Keynodes : public ScKeynodes
{
  public:
  // Ключевые узлы для разных вопросов
  static inline ScKeynode const action_soato_classification{"action_soato_classification", ScType::ConstNodeClass};
  // Ключевые узлы для различных типов отношений
  static inline ScKeynode const rrel_entity{"rrel_entity", ScType::ConstNodeRole};
};

}
