/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include <sc-memory/kpm/sc_agent.hpp>
#include "keynodes/DanceStudiosKeynodes.hpp"
#include "search/DanceStudiosByPropertyInNumericalRangeFinder.hpp"
#include <memory>

#include "SearchDanceStudiosByFoundingYearAgent.generated.hpp"

using namespace std;

namespace dance_studios
{

class SearchDanceStudiosByFoundingYearAgent : public ScAgent
{
  SC_CLASS(Agent, Event(DanceStudiosKeynodes::action_search_dance_studios_by_founding_year, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

}
