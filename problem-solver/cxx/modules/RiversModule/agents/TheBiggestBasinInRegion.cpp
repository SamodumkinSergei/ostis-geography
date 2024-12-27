/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "TheBiggestBasinInRegion.hpp"
#include "keynodes/RiverKeynodes.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

ScAddr TheBiggestBasinInRegion::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return RiverKeynodes::action_get_theBiggestBasinInRegion;
}

// ScResult TheBiggestBasinInRegion::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
ScResult TheBiggestBasinInRegion::DoProgram(ScAction & action)
{
  // if (!event.GetArc().IsValid())
  //   return action.FinishUnsuccessfully();

  
  auto const & [region] = action.GetArguments<1>();

   if (!m_context.IsElement(region))
   {
      SC_AGENT_LOG_ERROR("Action does not have argument.");

      return action.FinishWithError();
   }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, region, ScType::ConstPermPosArc, RiverKeynodes::nrel_region);
  ScAddr river;
  int number = 0;
  ScAddr riv;
  while (it1->Next())
  {
    river = it1->Get(0);
    ScIterator5Ptr it2 = m_context.CreateIterator5(
        river, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, RiverKeynodes::nrel_basin);
    while (it2->Next())
    {
      ScAddr num = it2->Get(2);
      std::string str = CommonUtils::getIdtf(&m_context, num, ScKeynodes::nrel_main_idtf);
      
      int n = std::atoi(str.c_str());
      if (number < n)
      {
        number = n;
        riv = river;
      }
    }
  }

  ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
  riv, ScType::Unknown, region, ScType::ConstPermPosArc, RiverKeynodes::nrel_region);

  if (iteratorToAddToAnswer->Next())
  {
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
  }

  
//todo(codegen-removal): replace AgentUtils:: usage
  // AgentUtils::usage(&m_context, actionNode);
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

// ScAddr TheBiggestBasinInRegion::GetEventSubscriptionElement() const
// {
//   return ScKeynodes::action_initiated;
// }
}  // namespace RiversModule
