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

#include "LongerRiver.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

SC_AGENT_IMPLEMENTATION(LongerRiver)
{
  if (!edgeAddr.IsValid())
  {
    SC_LOG_ERROR("Initial edge is not valid");
    return SC_RESULT_ERROR;
  }

  SC_LOG_INFO("----------LongerRiver begin----------");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr river1 = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!river1.IsValid())
  {
    SC_LOG_ERROR("First river node is not valid");
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }
  else
  {
    std::string river1_idtf = CommonUtils::getIdtf(ms_context.get(), river1, Keynodes::nrel_main_idtf);
    SC_LOG_INFO("First river main identifier: " + river1_idtf);
  }

  ScAddr river2 = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_2);

  if (!river2.IsValid())
  {
    SC_LOG_ERROR("Second river node is not valid");
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }
  else
  {
    std::string river2_idtf = CommonUtils::getIdtf(ms_context.get(), river2, Keynodes::nrel_main_idtf);
    SC_LOG_INFO("Second river main identifier: " + river2_idtf);
  }

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  ScIterator5Ptr river1_iterator = ms_context->Iterator5(
      river1, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_length);
  int river1_length = 0;
  while (river1_iterator->Next())
  {
    ScAddr len = river1_iterator->Get(2);
    std::string str = CommonUtils::getIdtf(ms_context.get(), len, Keynodes::nrel_main_idtf);
    river1_length = std::atoi(str.c_str());
    SC_LOG_INFO("First river length: " + str);
  }

  ScIterator5Ptr river2_iterator = ms_context->Iterator5(
      river2, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_length);
  int river2_length = 0;
  while (river2_iterator->Next())
  {
    ScAddr len = river2_iterator->Get(2);
    std::string str = CommonUtils::getIdtf(ms_context.get(), len, Keynodes::nrel_main_idtf);
    river2_length = std::atoi(str.c_str());
    SC_LOG_INFO("Second river length: " + str);
  }

  if (river1_length > river2_length)
  {
    SC_LOG_INFO("First river is longer");
    ScIterator5Ptr iteratorToAddToAnswer = ms_context->Iterator5(
        river1, ScType::Unknown, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_length);

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
    SC_LOG_INFO("Second river is longer");
    ScIterator5Ptr iteratorToAddToAnswer = ms_context->Iterator5(
        river2, ScType::Unknown, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_length);

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

  SC_LOG_INFO("----------LongerRiver end----------");
  AgentUtils::finishAgentWork(ms_context.get(), actionNode);
  return SC_RESULT_OK;
}

}  // namespace RiversModule
