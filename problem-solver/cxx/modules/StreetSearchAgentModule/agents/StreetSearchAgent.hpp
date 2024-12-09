#pragma once

#include <sc-memory/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
namespace StreetSearchAgentModule
{

class StreetSearchAgent : public ScActionInitiatedAgent
{
  public:
  ScAddr GetActionClass() const override;

  ScResult DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) override;

  ScAddr GetEventSubscriptionElement() const override;

  };

}  // namespace StreetSearchAgentModule
