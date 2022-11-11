#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "PharmacySearchByCityAndRegionAgent.generated.hpp"

namespace PharmacySearchByCityAndRegionAgentModule
{

class PharmacySearchByCityAndRegionAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_pharmacyByCityAndRegionSearch, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule
