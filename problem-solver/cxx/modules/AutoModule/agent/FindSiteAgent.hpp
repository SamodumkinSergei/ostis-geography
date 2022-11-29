/*
* Author Artsiom Salauyou
*/

#pragma once

#include "sc-memory/kpm/sc_agent.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "keynodes/AutoKeynodes.hpp"

#include "FindSiteAgent.generated.hpp"

namespace autoModule
{
class FindSiteAgent : public ScAgent
{
 SC_CLASS(Agent, Event(AutoKeynodes::action_SiteSearch, ScEvent::Type::AddOutputEdge))
 SC_GENERATED_BODY()

};
}  // namespace hotelModule
