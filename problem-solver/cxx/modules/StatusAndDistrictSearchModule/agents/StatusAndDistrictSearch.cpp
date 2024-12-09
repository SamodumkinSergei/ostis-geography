/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-memory/sc_memory.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "StatusAndDistrictSearch.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace StatusAndDistrictSearchModule
{

ScResult StatusAndDistrictSearch::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("begin");
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  ScAddr shop = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);

  if (!shop.IsValid())
  {
    SC_AGENT_LOG_ERROR("First parameter isn't valid.");
//todo(codegen-removal): replace AgentUtils:: usage
    //action.SetResult(answer);
    return action.FinishUnsuccessfully();
  }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, shop, ScType::ConstPermPosArc, Keynodes::nrel_district);
  ScAddr shop1;
  ScAddr shopResult;
  if (it1->Next())
  {
    shop = it1->Get(0);
    ScIterator5Ptr it2 = m_context.CreateIterator5(
        shop, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_status);
    if (it2->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, shopResult);
    }
    else
    {
      SC_AGENT_LOG_ERROR("There is no such shops");
    }
  }
  action.SetResult(answer);
     
  return action.FinishSuccessfully();
}

ScAddr StatusAndDistrictSearch::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::action_statusAndDistrictSearch;
}

ScAddr StatusAndDistrictSearch::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

}  // namespace StatusAndDistrictSearchModule
