#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "PharmacySearchByCityAndRegionAgent.hpp"
#include "keynodes/PharmacyKeynodes.hpp"

using namespace std;
using namespace utils;

namespace PharmacySearchByCityAndRegionAgentModule
{

ScAddr PharmacySearchByCityAndRegionAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return PharmacyKeynodes::action_pharmacyByCityAndRegionSearch;
}

// ScResult PharmacySearchByCityAndRegionAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action
ScResult PharmacySearchByCityAndRegionAgent::DoProgram(ScAction & action)
{
  // if (!event.GetArc().IsValid())
  //   return action.FinishUnsuccessfully();
  auto const & [pharmacy] = action.GetArguments<1>();

  if (!m_context.IsElement(pharmacy))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, pharmacy, ScType::ConstPermPosArc, PharmacyKeynodes::nrel_city);
  ScAddr pharmacy1;
  ScAddr pharmacyResult;
  if (it1->Next())
  {
    pharmacy1 = it1->Get(0);
    ScIterator5Ptr it2 = m_context.CreateIterator5(
        pharmacy1, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, PharmacyKeynodes::nrel_region);
    if (it2->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, pharmacyResult);
    }
    else
    {
      SC_AGENT_LOG_ERROR("There is no such pharmacy");
    }
  }

//todo(codegen-removal): replace AgentUtils:: usage
  // AgentUtils::usage(&m_context, actionNode);
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

// ScAddr PharmacySearchByCityAndRegionAgent::GetEventSubscriptionElement() const
// {
//   return ScKeynodes::action_initiated;
// }

}  // namespace PharmacySearchByCityAndRegionAgentModule
