#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "StreetSearchAgent.generated.hpp"

namespace StreetSearchAgentModule
{

class StreetSearchAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_streetByLenghtSearch, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule
