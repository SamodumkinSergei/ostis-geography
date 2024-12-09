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

#include "LargerVillageByPopulationInTheDistrict.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace VitebskVillagesModule
{

ScResult LargerVillageByPopulationInTheDistrict::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  ScAgentContext ms_context;
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("----------LargerVillageByPopulationInTheDistrict begin----------");
  ScAddr actionNode = ms_context.GetArcTargetElement(event.GetArc());

  ScAddr district =
      IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);

  if (!district.IsValid())
  {
    SC_AGENT_LOG_ERROR("District is not valid");
    return action.FinishUnsuccessfully();
  }

  ScAddr answer = ms_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it1 = ms_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, district, ScType::ConstPermPosArc, Keynodes::nrel_district);
  ScAddr village;
  int number = 0;
  ScAddr largestVillage{};
  while (it1->Next())
  {
    village = it1->Get(0);
    ScIterator5Ptr it2 = ms_context.CreateIterator5(
        village, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);
    while (it2->Next())
    {
      ScAddr num = it2->Get(2);
      std::string str = CommonUtils::getIdtf(&ms_context, num, Keynodes::nrel_main_idtf);
      SC_AGENT_LOG_INFO(str.c_str());
      int n = std::atoi(str.c_str());
      if (number < n)
      {
        number = n;
        largestVillage = village;
      }
    }
  }

  if (largestVillage.IsValid())
  {
    ScIterator5Ptr iteratorToAddToAnswer = ms_context.CreateIterator5(
        largestVillage, ScType::Unknown, district, ScType::ConstPermPosArc, Keynodes::nrel_district);

    if (iteratorToAddToAnswer->Next())
    {
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  else
  {
    SC_AGENT_LOG_WARNING("There is no largest village in this district");
  }

  ScAddr edgeToAnswer = ms_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  ms_context.GenerateConnector(ScType::ConstPermPosArc, ScKeynodes::nrel_result, edgeToAnswer);

  SC_AGENT_LOG_INFO("----------LargerVillageByPopulationInTheDistrict	 end----------");
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

ScAddr LargerVillageByPopulationInTheDistrict::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::question_largerVillageByPopulationInTheDistrict;
}

ScAddr LargerVillageByPopulationInTheDistrict::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;;
}
}  // namespace VitebskVillagesModule
