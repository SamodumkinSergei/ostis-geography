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

#include "MuseumsRegionSearch.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace MuseumsRegionSearchModule
{

SC_AGENT_IMPLEMENTATION(MuseumsRegionSearch)
{
  ScAddr actionNode = m_memoryCtx.GetEdgeTarget(edgeAddr);

  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("Museums region search begin");

  ScAddr museum = IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!museum.IsValid())
  {
    SC_LOG_ERROR("Parameter isn't valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr museumResult = m_memoryCtx.CreateNode(ScType::NodeConstStruct);
  m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, museumResult, museum);

  ScAddr key_sc_element;

  ScIterator5Ptr iterator5 = m_memoryCtx.Iterator5(
      ScType::Unknown, ScType::EdgeAccessConstPosPerm, museum, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_region);
  while (iterator5->Next())
  {
    key_sc_element = iterator5->Get(0);
    m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, museumResult, iterator5->Get(2));
  }

  ScAddr edgeToAnswer = ms_context->CreateEdge(ScType::EdgeDCommonConst, actionNode, museumResult);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::nrel_answer, edgeToAnswer);

  AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, true);
  SC_LOG_DEBUG("Museums region search finished");
  return SC_RESULT_OK;
}

}  // namespace MuseumsRegionSearchModule
