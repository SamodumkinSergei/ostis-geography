#pragma once

#include "sc-memory/kpm/sc_agent.hpp"

#include "keynodes/AdminKeynodes.hpp"

#include "GetAdminBuildingDistrict.generated.hpp"

namespace adminModule
{

class GetAdminBuildingDistrict : public ScAgent
{
  SC_CLASS(Agent, Event(AdminKeynodes::action_get_admin_building_district, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

private:
  bool checkActionClass(const ScAddr & actionNode);
};

}  // namespace adminModule
