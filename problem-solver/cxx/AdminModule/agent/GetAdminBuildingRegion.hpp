#pragma once

#include "sc-memory/kpm/sc_agent.hpp"

#include "keynodes/AdminKeynodes.hpp"

#include "GetAdminBuildingRegion.generated.hpp"

namespace adminModule
{

class GetAdminBuildingRegion : public ScAgent 
{
  
  SC_CLASS(Agent, Event(AdminKeynodes::action_get_admin_building_region, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

private:
  bool checkActionClass(const ScAddr & actionNode);
};

}
