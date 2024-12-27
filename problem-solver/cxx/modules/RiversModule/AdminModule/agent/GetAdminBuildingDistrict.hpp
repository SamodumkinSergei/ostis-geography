#pragma once

#include "sc-memory/sc_agent.hpp"

#include "keynodes/AdminKeynodes.hpp"

namespace adminModule
{

// class GetAdminBuildingDistrict: public ScAgent<ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc>>
class GetAdminBuildingDistrict : public ScActionInitiatedAgent
{
  public:
  ScAddr GetActionClass() const ;

  // ScResult DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) const ;
  ScResult DoProgram(ScAction & action) ;

  // ScAddr GetEventSubscriptionElement() const ;

  private:
  bool checkActionClass(const ScAddr & actionNode) const  ;
};

}  // namespace adminModule
