/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#include <sc-agents-common/utils/IteratorUtils.hpp>
#include "keynodes/DanceStudiosKeynodes.hpp"

#include "SearchDanceStudiosByTypeAgent.hpp"

using namespace std;
using namespace utils;
namespace dance_studios
{

ScAddr SearchDanceStudiosByTypeAgent::GetActionClass() const // Метод получения класса действия агента
{

  return DanceStudiosKeynodes::action_search_dance_studios_by_type;
}


ScResult SearchDanceStudiosByTypeAgent::DoProgram(ScAction & action) // Главный метод агента
{
  
  auto const & [first] = action.GetArguments<1>();

  // Проверка наличия аргумета
  if (!m_context.IsElement(first))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  std::unique_ptr<DanceStudiosByString> danceStudiosByString = std::make_unique<DanceStudiosByString>();

  // Вызов класса для поиска танцевальных студий по строковым данным
  ScAddr questionNode = m_context.GetArcTargetElement(first);
  ScAddr answer = danceStudiosByString->findDanceStudiosByString(
      &m_context, questionNode, DanceStudiosKeynodes::concept_type, DanceStudiosKeynodes::nrel_type);


  action.SetResult(answer); // Привязка структуры ответа к агенту
  return action.FinishSuccessfully();
}





}  
