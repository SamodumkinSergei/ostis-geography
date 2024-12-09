/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "sc-memory/sc_agent.hpp"

#include "keynodes/RiverKeynodes.hpp"
namespace RiversModule
{

class TheBiggestBasinInRegion : public ScActionInitiatedAgent
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

}  // namespace RiversModule
