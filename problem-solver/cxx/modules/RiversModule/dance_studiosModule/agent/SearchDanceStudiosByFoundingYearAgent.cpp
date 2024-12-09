/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <sc-agents-common/utils/IteratorUtils.hpp>
#include "keynodes/DanceStudiosKeynodes.hpp"

#include "SearchDanceStudiosByFoundingYearAgent.hpp"

using namespace std;
using namespace utils;
namespace dance_studios
{

ScAddr SearchDanceStudiosByFoundingYearAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return DanceStudiosKeynodes::action_search_dance_studios_by_founding_year;
}

// ScResult SearchDanceStudiosByFoundingYearAgent::DoProgram(ScActionInitiatedEvent const & event, ScAction & action)
// ScResult SearchDanceStudiosByFoundingYearAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
ScResult SearchDanceStudiosByFoundingYearAgent::DoProgram(ScAction & action)
{

  auto const & [first] = action.GetArguments<1>();

  if (!m_context.IsElement(first))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }


  std::unique_ptr<DanceStudiosByPropertyInNumericalRangeFinder> danceStudiosByPropertyInNumericalRangeFinder =
      std::make_unique<DanceStudiosByPropertyInNumericalRangeFinder>();
  // ScMemoryContext * memory_ctx;


  ScAddr questionNode = m_context.GetArcTargetElement(first);
  ScAddr answer = danceStudiosByPropertyInNumericalRangeFinder->findDanceStudiosByPropertyInNumericalRange(
      &m_context,
      questionNode,
      DanceStudiosKeynodes::concept_year_of_foundation,
      DanceStudiosKeynodes::nrel_year_of_foundation);

  if (!answer.IsValid())
  {
    return action.FinishUnsuccessfully();
  }


  action.SetResult(answer);
  return action.FinishSuccessfully();
}

}

