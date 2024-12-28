#pragma once

#include <sc-memory/sc_agent.hpp>

#include "keynodes/PharmacyKeynodes.hpp"
namespace PharmacySearchByCityAndRegionAgentModule
{

class PharmacySearchByCityAndRegionAgent : public ScActionInitiatedAgent
{

  public:
  ScAddr GetActionClass() const override;

  // ScResult DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) const override;
  ScResult DoProgram(ScAction & action) override;

  // public:
  // ScAddr GetActionClass() const override;

  // ScResult DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) override;

  // ScAddr GetEventSubscriptionElement() const override;

  };

}  // namespace PharmacySearchByCityAndRegionAgentModule
