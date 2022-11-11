#pragma once

#include "sc-memory/kpm/sc_agent.hpp"

#include "keynodes/AdminKeynodes.hpp"

#include "GetEmbassy.generated.hpp"

namespace adminModule
{

class GetEmbassy : public ScAgent 
{
  
  SC_CLASS(Agent, Event(AdminKeynodes::action_get_embassy, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

private:
  bool checkActionClass(const ScAddr & actionNode);
};

}
