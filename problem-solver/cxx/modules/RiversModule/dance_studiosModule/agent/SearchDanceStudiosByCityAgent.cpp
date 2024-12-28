/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <sc-agents-common/utils/IteratorUtils.hpp>
#include "keynodes/DanceStudiosKeynodes.hpp"

#include "SearchDanceStudiosByCityAgent.hpp"

using namespace std;
using namespace utils;
namespace dance_studios
{

ScAddr SearchDanceStudiosByCityAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return DanceStudiosKeynodes::action_search_dance_studios_by_city;
}

// ScResult SearchDanceStudiosByCityAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
ScResult SearchDanceStudiosByCityAgent::DoProgram(ScAction & action)
{
  auto const & [first] = action.GetArguments<1>();

  if (!m_context.IsElement(first))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  std::unique_ptr<DanceStudiosByString> danceStudiosByString = std::make_unique<DanceStudiosByString>();

  ScAddr questionNode = m_context.GetArcTargetElement(first);
  ScAddr answer = danceStudiosByString->findDanceStudiosByString(
      &m_context, questionNode, DanceStudiosKeynodes::concept_city, DanceStudiosKeynodes::nrel_city);


//todo(codegen-removal): replace AgentUtils:: usage
  // AgentUtils::usage((ScMemoryContext *)&m_context, questionNode, success);
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

}

