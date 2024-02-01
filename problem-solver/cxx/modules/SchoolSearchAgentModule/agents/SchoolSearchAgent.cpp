#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "SchoolSearchAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace SchoolSearchAgentModule
{

SC_AGENT_IMPLEMENTATION(SchoolSearchAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("SchoolSearchAgent begin");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr school = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!school.IsValid())
  {
    SC_LOG_ERROR("First parameter isn't valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  ScIterator5Ptr it1 = ms_context->Iterator5(
      ScType::Unknown, ScType::EdgeDCommonConst, school, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_school_number);
  ScAddr school1;
  ScAddr schoolResult;
  if (it1->Next())
  {
    school = it1->Get(0);
    ScIterator5Ptr it2 = ms_context->Iterator5(
        school, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_search_area);
    if (it2->Next())
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, schoolResult);
    }
    else
    {
      SC_LOG_ERROR("There is no such school");
    }
  }

  ScAddr edgeToAnswer = ms_context->CreateEdge(ScType::EdgeDCommonConst, actionNode, answer);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::nrel_answer, edgeToAnswer);

  AgentUtils::finishAgentWork(ms_context.get(), actionNode);
  SC_LOG_INFO("SchoolSearchAgent end");
  return SC_RESULT_OK;
}

}  // namespace SchoolSearchAgentModule
