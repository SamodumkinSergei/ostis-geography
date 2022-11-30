/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <sc-memory/sc_stream.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>

#include <iostream>
#include "VillageSearchAgent.hpp"

using namespace std;
using namespace utils;

namespace VillagesModule
{

ScAddr getVillageNode(ScLog * logger, std::unique_ptr<ScMemoryContext> & ms_context, ScAddr set)
{
  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  ScAddr first = ms_context->HelperFindBySystemIdtf("nrel_Vitebsk_village");
  logger->Message(ScLog::Type::Info, "Villages Vitebsk " + ms_context->HelperGetSystemIdtf(set));

  ScIterator5Ptr iter =
      ms_context->Iterator5(set, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, first);
  while (iter->Next())
  {
    SC_LOG_ERROR("Found Vitebsk village");
    logger->Message(ScLog::Type::Info, "Village: " + ms_context->HelperGetSystemIdtf(iter->Get(2)));
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter->Get(2));
    return answer;
  }
  logger->Message(ScLog::Type::Info, "village not found");

  return answer;
}

SC_AGENT_IMPLEMENTATION(VillageSearchAgent)
{
  SC_LOG_ERROR("VillageSearchAgent started");
  ScLog * logger = ScLog::GetInstance();

  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr node = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!node.IsValid())
  {
    SC_LOG_ERROR("Arg not found");
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr answer = getVillageNode(logger, ms_context, node);

  utils::AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);

  return SC_RESULT_OK;
}
}  // namespace VillagesModule
