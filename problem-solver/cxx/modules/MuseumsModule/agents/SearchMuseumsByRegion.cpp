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

#include "SearchMuseumsByRegion.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace MuseumsModule
{

SC_AGENT_IMPLEMENTATION(SearchMuseumsByRegion)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("----------SearchMuseumsByRegion begin----------");

  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr region = IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!region.IsValid())
  {
    SC_LOG_ERROR("Region node is not valid.");
    AgentUtils::finishAgentWork(ms_context.get(), actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }
  else
  {
    std::string region_idtf = CommonUtils::getIdtf(ms_context.get(), region, Keynodes::nrel_main_idtf);
    SC_LOG_DEBUG("Region main identifier: " + region_idtf);
  }

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  ScIterator5Ptr iterator5 = ms_context->Iterator5(
      ScType::Unknown, ScType::EdgeDCommonConst, region, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_region);
  while (iterator5->Next())
  {
    ScAddr addr = iterator5->Get(0);

    ScIterator3Ptr iterator3 = ms_context->Iterator3(Keynodes::concept_museum, ScType::EdgeAccessConstPosPerm, addr);
    if (iterator3->Next())
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, addr);
      std::string museum_idtf = CommonUtils::getIdtf(ms_context.get(), addr, Keynodes::nrel_main_idtf);
      SC_LOG_DEBUG("Museum main identifier: " + museum_idtf);
    }
  }

  SC_LOG_INFO("----------SearchMuseumsByRegion end----------");
  AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer, true);
  return SC_RESULT_OK;
}

}  // namespace MuseumsModule
