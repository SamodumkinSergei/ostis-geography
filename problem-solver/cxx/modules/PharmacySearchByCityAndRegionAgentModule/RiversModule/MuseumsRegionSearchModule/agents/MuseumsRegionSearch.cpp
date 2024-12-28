/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "MuseumsRegionSearch.hpp"
#include "keynodes/MuseumKeynodes.hpp"

using namespace std;
using namespace utils;

namespace MuseumsRegionSearchModule
{

ScAddr MuseumsRegionSearch::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return MuseumKeynodes::action_museumsRegionSearch;
}

// ScResult MuseumsRegionSearch::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
ScResult MuseumsRegionSearch::DoProgram(ScAction & action)
{
  auto const & [museum] = action.GetArguments<1>();

  if (!m_context.IsElement(museum))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  ScAddr museumResult = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScAddr key_sc_element;

  ScIterator5Ptr iterator5 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstPermPosArc, museum, ScType::ConstPermPosArc, MuseumKeynodes::nrel_region);
  while (iterator5->Next())
  {
    key_sc_element = iterator5->Get(0);
    m_context.GenerateConnector(ScType::ConstPermPosArc, museumResult, iterator5->Get(2));
  }

  action.SetResult(museumResult);
  return action.FinishSuccessfully();
}

// ScAddr MuseumsRegionSearch::GetEventSubscriptionElement() const
// {
//   return ScKeynodes::action_initiated;
// }

}  // namespace MuseumsRegionSearchModule
