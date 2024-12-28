/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#include <sc-agents-common/utils/IteratorUtils.hpp>
#include "keynodes/DanceStudiosKeynodes.hpp"

#include "SearchDanceStudiosByFoundingYearAgent.hpp"

using namespace std;
using namespace utils;
namespace dance_studios
{

ScAddr SearchDanceStudiosByFoundingYearAgent::GetActionClass() const // Метод получения класса действия агента
{
  return DanceStudiosKeynodes::action_search_dance_studios_by_founding_year;
}



ScResult SearchDanceStudiosByFoundingYearAgent::DoProgram(ScAction & action) // Главный метод агента
{

  auto const & [first] = action.GetArguments<1>(); // Получение аргумента

  // Проверка наличия аргумента
  if (!m_context.IsElement(first))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }


  std::unique_ptr<DanceStudiosByPropertyInNumericalRangeFinder> danceStudiosByPropertyInNumericalRangeFinder =
      std::make_unique<DanceStudiosByPropertyInNumericalRangeFinder>();
  

  // Вызов класса для поиска танцевальных студий по числовому свойству
  ScAddr questionNode = m_context.GetArcTargetElement(first);
  ScAddr answer = danceStudiosByPropertyInNumericalRangeFinder->findDanceStudiosByPropertyInNumericalRange(
      &m_context,
      questionNode,
      DanceStudiosKeynodes::concept_year_of_foundation,
      DanceStudiosKeynodes::nrel_year_of_foundation);

  // Проверка наличия ответа
  if (!answer.IsValid())
  {
    return action.FinishUnsuccessfully();
  }


  action.SetResult(answer); // Привязка структуры ответа к агенту
  return action.FinishSuccessfully();
}

}

