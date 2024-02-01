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

#include "PotteryDate.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace PotteryModule
{

SC_AGENT_IMPLEMENTATION(PotteryDate)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("----------PotteryDate begin----------");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr date1 = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  ScAddr date2 = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_2);

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  std::string str1 = CommonUtils::getIdtf(ms_context.get(), date1, Keynodes::nrel_main_idtf);
  std::string str2 = CommonUtils::getIdtf(ms_context.get(), date2, Keynodes::nrel_main_idtf);
  SC_LOG_INFO(str1.c_str());
  SC_LOG_INFO(str2.c_str());
  int d1 = std::atoi(str1.c_str());
  int d2 = std::atoi(str2.c_str());

  ScIterator3Ptr it2 = ms_context->Iterator3(Keynodes::pottery_centre, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
  ScAddr smth;
  while (it2->Next())
  {
    smth = it2->Get(2);
    ScIterator5Ptr it1 = ms_context->Iterator5(
        smth, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_date);
    ScAddr date;
    while (it1->Next())
    {
      date = it1->Get(2);
      std::string str = CommonUtils::getIdtf(ms_context.get(), date, Keynodes::nrel_main_idtf);
      SC_LOG_INFO(str.c_str());
      int d = std::atoi(str.c_str());
      if (d < d2)
      {
        if (d > d1)
        {
          ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, smth);
        }
      }
    }
  }

  ScAddr edgeToAnswer = ms_context->CreateEdge(ScType::EdgeDCommonConst, actionNode, answer);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::nrel_answer, edgeToAnswer);

  SC_LOG_INFO("----------PotteryDate end----------");
  AgentUtils::finishAgentWork(ms_context.get(), actionNode);
  return SC_RESULT_OK;
}
}  // namespace PotteryModule
