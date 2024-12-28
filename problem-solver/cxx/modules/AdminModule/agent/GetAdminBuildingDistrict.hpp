#pragma once

#include "sc-memory/sc_agent.hpp"

#include "keynodes/AdminKeynodes.hpp"

namespace adminModule
{


class GetAdminBuildingDistrict : public ScActionInitiatedAgent
{
  public:
  ScAddr GetActionClass() const; // Метод получения класса действия агента
  ScResult DoProgram(ScAction & action) override; // Главный метод агента

};

}  
