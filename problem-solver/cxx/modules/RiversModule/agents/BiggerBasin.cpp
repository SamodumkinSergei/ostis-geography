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

#include "BiggerBasin.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

SC_AGENT_IMPLEMENTATION(BiggerBasin)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("----------BiggerBasin begin----------");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr river1 = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  std::string river1_idtf = CommonUtils::getIdtf(ms_context.get(), river1, Keynodes::nrel_main_idtf);
  SC_LOG_INFO("First river is " + river1_idtf);

  ScAddr river2 = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_2);

  std::string river2_idtf = CommonUtils::getIdtf(ms_context.get(), river2, Keynodes::nrel_main_idtf);
  SC_LOG_INFO("Second river is " + river2_idtf);

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  ScIterator5Ptr it = ms_context->Iterator5(
      river1, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_basin);
  int l1 = 0;
  while (it->Next())
  {
    ScAddr len = it->Get(2);
    std::string str1 = CommonUtils::getIdtf(ms_context.get(), len, Keynodes::nrel_main_idtf);
    l1 = std::atoi(str1.c_str());
  }

  ScIterator5Ptr it1 = ms_context->Iterator5(
      river2, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_basin);
  int l2 = 0;
  while (it1->Next())
  {
    ScAddr len = it1->Get(2);
    std::string str2 = CommonUtils::getIdtf(ms_context.get(), len, Keynodes::nrel_main_idtf);
    l2 = std::atoi(str2.c_str());
  }

  if (l1 > l2)
  {
    ScIterator5Ptr iteratorToAddToAnswer = ms_context->Iterator5(
        river1, ScType::Unknown, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_basin);

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
    ScIterator5Ptr iteratorToAddToAnswer = ms_context->Iterator5(
        river2, ScType::Unknown, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_basin);

    if (iteratorToAddToAnswer->Next())
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(0));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(1));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(2));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(3));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(4));
    }
  }

  ScAddr edgeToAnswer = ms_context->CreateEdge(ScType::EdgeDCommonConst, actionNode, answer);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::nrel_answer, edgeToAnswer);

  SC_LOG_INFO("----------BiggerBasin end----------");
  AgentUtils::finishAgentWork(ms_context.get(), actionNode);
  return SC_RESULT_OK;
}
}  // namespace RiversModule
