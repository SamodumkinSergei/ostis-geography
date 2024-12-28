/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#pragma once

#include <sc-memory/sc_agent.hpp>
#include "keynodes/DanceStudiosKeynodes.hpp"
#include "search/DanceStudiosByPropertyInNumericalRangeFinder.hpp"
#include <memory>



using namespace std;

namespace dance_studios
{

class SearchDanceStudiosByFoundingYearAgent : public ScActionInitiatedAgent
{

  public:
  ScAddr GetActionClass() const override; // Метод получения класса действий агента 
  
  ScResult DoProgram(ScAction & action) // Главный метод агента
};

}  
