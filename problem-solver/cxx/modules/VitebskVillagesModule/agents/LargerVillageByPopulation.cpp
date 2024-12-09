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

#include "LargerVillageByPopulation.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace VitebskVillagesModule
{

ScResult LargerVillageByPopulation::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("----------LargerVillageByPopulation start----------");
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  ScAddr village1 =
      IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);

  ScAddr village2 =
      IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_2);
  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it = m_context.CreateIterator5(
      village1, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);
  int l1 = 0;
  while (it->Next())
  {
    ScAddr len = it->Get(2);
    std::string str1 = CommonUtils::getIdtf(&m_context, len, Keynodes::nrel_main_idtf);
    l1 = std::atoi(str1.c_str());
    SC_AGENT_LOG_INFO(str1);
  }

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      village2, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);
  int l2 = 0;
  while (it1->Next())
  {
    ScAddr len = it1->Get(2);
    std::string str2 = CommonUtils::getIdtf(&m_context, len, Keynodes::nrel_main_idtf);
    l2 = std::atoi(str2.c_str());
    SC_AGENT_LOG_INFO(str2);
  }

  if (l1 > l2)
  {
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        village1, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);

    if (iteratorToAddToAnswer->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  else
  {
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        village2, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);

    if (iteratorToAddToAnswer->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }

  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  m_context.GenerateConnector(ScType::ConstPermPosArc,ScKeynodes::nrel_result, edgeToAnswer);
  SC_AGENT_LOG_INFO("----------LargerVillageByPopulation end----------");
action.SetResult(answer);
  return action.FinishSuccessfully();
}

ScAddr LargerVillageByPopulation::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::question_largerVillageByPopulation;
}

ScAddr LargerVillageByPopulation::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;;
}
}  // namespace VitebskVillagesModule
