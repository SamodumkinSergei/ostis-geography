#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "StreetSearchAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace StreetSearchAgentModule
{

SC_AGENT_IMPLEMENTATION(StreetSearchAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("StreetSearchAgent begin");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr street = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!street.IsValid())
  {
    SC_LOG_ERROR("First parameter isn't valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  ScIterator5Ptr it1 = ms_context->Iterator5(
      ScType::Unknown, ScType::EdgeDCommonConst, street, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_street_length);
  ScAddr street1;
  ScAddr streetResult;
  if (it1->Next())
  {
    street = it1->Get(0);
    ScIterator5Ptr it2 = ms_context->Iterator5(
        street, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_search_area);
    if (it2->Next())
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, streetResult);
    }
    else
    {
      SC_LOG_ERROR("There is no such street");
    }
  }

  ScAddr edgeToAnswer = ms_context->CreateEdge(ScType::EdgeDCommonConst, actionNode, answer);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::nrel_answer, edgeToAnswer);

  AgentUtils::finishAgentWork(ms_context.get(), actionNode);
  SC_LOG_INFO("StreetSearchAgent end");
  return SC_RESULT_OK;
}

}  // namespace StreetSearchAgentModule
