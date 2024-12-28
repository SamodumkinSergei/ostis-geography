#pragma once

#include "sc-memory/sc_agent.hpp"

#include "keynodes/AdminKeynodes.hpp"

namespace adminModule
{

class GetAdminBuildingRegion : public ScActionInitiatedAgent
// class GetAdminBuildingRegion: public ScActionInitiatedAgent
{
  public:
  ScAddr GetActionClass() const ;

  ScResult DoProgram(ScAction & action) ;
  // ScResult DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) const ;

  // ScAddr GetEventSubscriptionElement() const ;

  private:
  bool checkActionClass(const ScAddr & actionNode) const ;
};

}  // namespace adminModule
