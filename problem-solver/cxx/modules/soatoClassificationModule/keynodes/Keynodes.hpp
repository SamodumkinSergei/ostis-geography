#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace soatoClassificationModule
{

class Keynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_soato_classification{"action_soato_classification", ScType::ConstNodeClass};
  static inline ScKeynode const rrel_entity{"rrel_entity", ScType::ConstNodeRole};
};

}
