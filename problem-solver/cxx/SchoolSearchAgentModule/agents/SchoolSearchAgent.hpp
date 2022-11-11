#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "SchoolSearchAgent.generated.hpp"

namespace SchoolSearchAgentModule
{

class SchoolSearchAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_schoolByNumberSearch, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

}  // namespace SchoolSearchAgentModule
