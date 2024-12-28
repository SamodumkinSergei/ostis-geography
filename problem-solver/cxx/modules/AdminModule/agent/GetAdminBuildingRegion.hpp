#pragma once

#include "sc-memory/sc_agent.hpp"

#include "keynodes/AdminKeynodes.hpp"

namespace adminModule
{

class GetAdminBuildingRegion : public ScActionInitiatedAgent

{
  public:
  ScAddr GetActionClass() const; // Метод получения класса действия 

  ScResult DoProgram(ScAction & action) override; // Главный метод агента
};

}  
