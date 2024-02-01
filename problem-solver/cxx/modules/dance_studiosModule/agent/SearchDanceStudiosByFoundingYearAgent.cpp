/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <sc-agents-common/keynodes/coreKeynodes.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>

#include "keynodes/DanceStudiosKeynodes.hpp"

#include "SearchDanceStudiosByFoundingYearAgent.hpp"

using namespace std;
using namespace utils;
using namespace scAgentsCommon;

namespace dance_studios
{

SC_AGENT_IMPLEMENTATION(SearchDanceStudiosByFoundingYearAgent)
{
  SC_LOG_INFO("agent start");

  if (!edgeAddr.IsValid())
  {
    return SC_RESULT_ERROR;
  }

  std::unique_ptr<DanceStudiosByPropertyInNumericalRangeFinder> danceStudiosByPropertyInNumericalRangeFinder =
      std::make_unique<DanceStudiosByPropertyInNumericalRangeFinder>();

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr answer = danceStudiosByPropertyInNumericalRangeFinder->findDanceStudiosByPropertyInNumericalRange(
      ms_context.get(),
      questionNode,
      DanceStudiosKeynodes::concept_year_of_foundation,
      DanceStudiosKeynodes::nrel_year_of_foundation);

  if (!answer.IsValid())
  {
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  bool success = ms_context->HelperCheckEdge(
      DanceStudiosKeynodes::concept_success_solution, answer, ScType::EdgeAccessConstPosPerm);

  ScAddr edgeToAnswer = ms_context->CreateEdge(ScType::EdgeDCommonConst, questionNode, answer);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::nrel_answer, edgeToAnswer);

  AgentUtils::finishAgentWork((ScMemoryContext *)ms_context.get(), questionNode, success);

  return SC_RESULT_OK;
}
}  // namespace dance_studios
