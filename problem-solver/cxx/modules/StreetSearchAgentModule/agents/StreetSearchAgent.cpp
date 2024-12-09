#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-memory/sc_memory.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "StreetSearchAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace StreetSearchAgentModule
{

ScResult StreetSearchAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("begin");
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  ScAddr street = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);

  if (!street.IsValid())
  {
    SC_AGENT_LOG_ERROR("First parameter isn't valid.");
//todo(codegen-removal): replace AgentUtils:: usage
   // AgentUtils::finishAgentWork(&m_context, actionNode, false);
    return action.FinishUnsuccessfully();
  }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, street, ScType::ConstPermPosArc, Keynodes::nrel_street_length);
  ScAddr street1;
  ScAddr streetResult;
  if (it1->Next())
  {
    street = it1->Get(0);
    ScIterator5Ptr it2 = m_context.CreateIterator5(
        street, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_search_area);
    if (it2->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, streetResult);
    }
    else
    {
      SC_AGENT_LOG_ERROR("There is no such street");
    }
  }

  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  action.SetResult(answer);
  SC_AGENT_LOG_INFO("end");
  return action.FinishSuccessfully();
}

ScAddr StreetSearchAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::action_streetByLenghtSearch;
}

ScAddr StreetSearchAgent::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;;
}

}  // namespace StreetSearchAgentModule
