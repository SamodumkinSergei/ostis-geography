/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>

#include "ShorterRiver.hpp"
#include "keynodes/RiverKeynodes.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

ScAddr ShorterRiver::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return RiverKeynodes::action_get_shorterRiver;
}

// ScResult ShorterRiver::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
ScResult ShorterRiver::DoProgram(ScAction & action)
{
  // if (!event.GetArc().IsValid())
  //   return action.FinishUnsuccessfully();

  auto const & [river1, river2] = action.GetArguments<2>();

  if (!m_context.IsElement(river1))
  {
    SC_AGENT_LOG_ERROR("Action does not have first argument.");
    return action.FinishWithError();
  }

  if (!m_context.IsElement(river2))
  {
    SC_AGENT_LOG_ERROR("Action does not have second argument.");
    return action.FinishWithError();
  }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it = m_context.CreateIterator5(
      river1, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, RiverKeynodes::nrel_length);
  int l1 = 0;
  while (it->Next())
  {
    ScAddr len = it->Get(2);
    std::string str1 = CommonUtils::getIdtf(&m_context, len, ScKeynodes::nrel_main_idtf);
    l1 = std::atoi(str1.c_str());
  }

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      river2, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, RiverKeynodes::nrel_length);
  int l2 = 0;
  while (it1->Next())
  {
    ScAddr len = it1->Get(2);
    std::string str2 = CommonUtils::getIdtf(&m_context, len, ScKeynodes::nrel_main_idtf);
    l2 = std::atoi(str2.c_str());
  }

  if (l1 < l2)
  {
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        river1, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, RiverKeynodes::nrel_length);

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
        river2, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, RiverKeynodes::nrel_length);

    if (iteratorToAddToAnswer->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

// ScAddr ShorterRiver::GetEventSubscriptionElement() const
// {
//   return ScKeynodes::action_initiated;
// }

}  // namespace RiversModule
