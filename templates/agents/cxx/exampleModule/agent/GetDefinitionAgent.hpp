#pragma once

#include "sc-memory/kpm/sc_agent.hpp"

#include "keynodes/ExampleKeynodes.hpp"

#include "GetDefinitionAgent.generated.hpp"

namespace exampleModule
{

class GetDefinitionAgent : public ScAgent // название агента может быть любое
{
  // тут задается событие на которое реагирует агент
  // в данном случае агент сработает если от узла action_get_definition создастся дуга.
  SC_CLASS(Agent, Event(ExampleKeynodes::action_get_definition, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

private:
  bool checkActionClass(const ScAddr & actionNode);
  // тут ваши методы и поля
  std::string getDefinition(const ScAddr & node);
};

}
