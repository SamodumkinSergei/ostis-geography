/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#pragma once

#include "sc-memory/sc_agent.hpp"

#include "keynodes/RiverKeynodes.hpp"
namespace RiversModule
{

class LongestInRegion : public ScActionInitiatedAgent
{

  public:
  ScAddr GetActionClass() const override; // Метод получения класса действия агента
  ScResult DoProgram(ScAction & action) override; // Главный метод агента

  };

}  
