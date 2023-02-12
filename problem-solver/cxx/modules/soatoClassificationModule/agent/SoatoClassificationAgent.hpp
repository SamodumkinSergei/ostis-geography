#pragma once

#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "sc-memory/kpm/sc_agent.hpp"

#include "SoatoClassificationAgent.generated.hpp"

namespace soatoClassificationModule
{

class SoatoClassificationManager;

class SoatoClassificationAgent : public ScAgent
{
  SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY();

private:
  bool checkActionClass(ScAddr const & actionAddr);
};

}  // namespace soatoClassificationModule
