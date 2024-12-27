/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>

#include "LongerRiver.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

ScAddr LongerRiver::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return RiverKeynodes::action_get_longerRiver;
}

// ScResult LongerRiver::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
ScResult LongerRiver::DoProgram(ScAction & action)
{ 
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

  ScIterator5Ptr river1_iterator = m_context.CreateIterator5(
      river1, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, RiverKeynodes::nrel_length);
  int river1_length = 0;
  while (river1_iterator->Next())
  {
    ScAddr len = river1_iterator->Get(2);
    std::string str = CommonUtils::getIdtf(&m_context, len, ScKeynodes::nrel_main_idtf);
    river1_length = std::atoi(str.c_str());
    
  }

  ScIterator5Ptr river2_iterator = m_context.CreateIterator5(
      river2, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, RiverKeynodes::nrel_length);
  int river2_length = 0;
  while (river2_iterator->Next())
  {
    ScAddr len = river2_iterator->Get(2);
    std::string str = CommonUtils::getIdtf(&m_context, len, ScKeynodes::nrel_main_idtf);
    river2_length = std::atoi(str.c_str());
    
  }

  if (river1_length > river2_length)
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

}  // namespace RiversModule
