/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/keynodes/coreKeynodes.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>

#include "keynodes/DanceStudiosKeynodes.hpp"

#include "SearchDanceStudiosByCityAgent.hpp"

using namespace std;
using namespace utils;
using namespace scAgentsCommon;

namespace dance_studios {

  SC_AGENT_IMPLEMENTATION(SearchDanceStudiosByCityAgent)
  {

    SC_LOG_INFO("agent start");


    if (!edgeAddr.IsValid()) {
      return SC_RESULT_ERROR;
    }


    std::unique_ptr<DanceStudiosByString>
        danceStudiosByString =
        std::make_unique<DanceStudiosByString>();

    ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
    ScAddr answer = danceStudiosByString->
        findDanceStudiosByString(
        ms_context.get(),
        questionNode,
        DanceStudiosKeynodes::concept_city,
        DanceStudiosKeynodes::nrel_city);

    if (!answer.IsValid()) {
      return SC_RESULT_ERROR_INVALID_PARAMS;
    }

    bool success = ms_context->HelperCheckEdge(DanceStudiosKeynodes::concept_success_solution,
                                               answer, ScType::EdgeAccessConstPosPerm);
    AgentUtils::finishAgentWork((ScMemoryContext *) ms_context.get(),
                                questionNode, answer, success);

    return SC_RESULT_OK;
  }
}
