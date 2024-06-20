/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "SmallerVillageByPopulationInTheDistrict.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace VitebskVillagesModule
{

SC_AGENT_IMPLEMENTATION(SmallerVillageByPopulationInTheDistrict)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("----------SmallerVillageByPopulationInTheDistrict begin----------");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr district =
      IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!district.IsValid())
  {
    SC_LOG_ERROR("District is not valid");
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  ScIterator5Ptr it1 = ms_context->Iterator5(
      ScType::Unknown, ScType::EdgeDCommonConst, district, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_district);
  ScAddr village;
  int number = 1000000;
  ScAddr smallestVillage{};
  while (it1->Next())
  {
    village = it1->Get(0);
    ScIterator5Ptr it2 = ms_context->Iterator5(
        village, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_population);
    while (it2->Next())
    {
      ScAddr num = it2->Get(2);
      std::string str = CommonUtils::getIdtfValue(ms_context.get(), num, Keynodes::nrel_main_idtf);
      SC_LOG_INFO(str.c_str());
      int n = std::atoi(str.c_str());
      if (number > n)
      {
        number = n;
        smallestVillage = village;
      }
    }
  }

  if (smallestVillage.IsValid())
  {
    ScIterator5Ptr iteratorToAddToAnswer = ms_context->Iterator5(
        smallestVillage, ScType::Unknown, district, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_district);

    if (iteratorToAddToAnswer->Next())
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(0));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(1));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(2));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(3));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  else
  {
    SC_LOG_WARNING("There is no smallest village in this district");
  }

  SC_LOG_INFO("----------SmallerVillageByPopulationInTheDistrict	 end----------");
  AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
  return SC_RESULT_OK;
}
}  // namespace VitebskVillagesModule
