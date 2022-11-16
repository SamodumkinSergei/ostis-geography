/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>

#include "LongestInRegion.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

SC_AGENT_IMPLEMENTATION(LongestInRegion)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("----------LongestInRegion begin----------");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr region = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!region.IsValid())
  {
    SC_LOG_ERROR("region is not valid");
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  std::string regionIdtf = CommonUtils::getIdtf(ms_context.get(), region, Keynodes::nrel_main_idtf);
  SC_LOG_INFO("region is " + regionIdtf);

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  int maxLength = 0;
  ScAddr longestRiverAddr{};

  auto iteratorForRivers = ms_context->Iterator5(
      ScType::Unknown, ScType::EdgeDCommonConst, region, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_region);
  while (iteratorForRivers->Next())
  {
    ScAddr riverAddr = iteratorForRivers->Get(0);
    std::string riverName = CommonUtils::getIdtf(ms_context.get(), riverAddr, Keynodes::nrel_main_idtf);
    auto iteratorForLength = ms_context->Iterator5(
        riverAddr, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_length);

    while (iteratorForLength->Next())
    {
      ScAddr lengthAddr = iteratorForLength->Get(2);
      std::string lengthStr = CommonUtils::getIdtf(ms_context.get(), lengthAddr, Keynodes::nrel_main_idtf);
      SC_LOG_INFO("Found river " + riverName + " with length " + lengthStr);
      int lengthInt = std::stoi(lengthStr);
      if (maxLength < lengthInt)
      {
        maxLength = lengthInt;
        longestRiverAddr = riverAddr;
      }
    }
  }

  if (longestRiverAddr.IsValid())
  {
    std::string riverName = CommonUtils::getIdtf(ms_context.get(), longestRiverAddr, Keynodes::nrel_main_idtf);
    SC_LOG_INFO("longest river in " + regionIdtf + " is " + riverName);

    ScIterator5Ptr iteratorToAddToAnswer = ms_context->Iterator5(
        longestRiverAddr, ScType::Unknown, region, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_region);

    if (iteratorToAddToAnswer->Next())
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(0));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(1));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(2));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(3));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(4));
    }
  }

  SC_LOG_INFO("----------LongestInRegion end----------");
  AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
  return SC_RESULT_OK;
}
}  // namespace RiversModule
