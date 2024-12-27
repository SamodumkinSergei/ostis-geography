/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-memory/sc_memory.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "StatusAndDistrictSearch.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace StatusAndDistrictSearchModule
{

/* 
 * Метод DoProgram выполняет основную логику агента, который реагирует на событие 
 * создания исходящей дуги (ScEventAfterGenerateOutgoingArc). Агент ищет магазин,
 * связанный с определенным параметром, и проверяет его статус и район.
 */
ScResult StatusAndDistrictSearch::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  // Проверка на валидность дуги события. Если она невалидна, завершаем агент с ошибкой
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("begin");

  // Получаем целевой узел дуги, который является элементом действия
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  // Используем утилиту для получения магазина, связанного с данным действием
  ScAddr shop = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);

  // Проверяем, найден ли магазин. Если магазин не найден, завершаем агент с ошибкой.
  if (!shop.IsValid())
  {
    SC_AGENT_LOG_ERROR("First parameter isn't valid.");
    // Можно заменить использование AgentUtils (комментарий "todo")
    return action.FinishUnsuccessfully();
  }

  // Создаем узел, в котором будет храниться результат
  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  // Создаем итератор для поиска района, связанного с магазином через отношение nrel_district
  ScIterator5Ptr it1 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, shop, ScType::ConstPermPosArc, Keynodes::nrel_district);
  
  ScAddr shop1;
  ScAddr shopResult;

  // Если район найден, продолжаем искать статус
  if (it1->Next())
  {
    shop = it1->Get(0);

    // Создаем второй итератор для поиска статуса магазина через отношение nrel_status
    ScIterator5Ptr it2 = m_context.CreateIterator5(
        shop, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_status);
    
    // Если статус найден, добавляем связь между результатом и магазином
    if (it2->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, shopResult);
    }
    else
    {
      // Если статус не найден, выводим сообщение об ошибке
      SC_AGENT_LOG_ERROR("There is no such shops");
    }
  }

  // Устанавливаем результат действия
  action.SetResult(answer);
     
  // Завершаем выполнение действия с успешным результатом
  return action.FinishSuccessfully();
}

/*
 * Метод GetActionClass возвращает класс действия, с которым работает агент.
 * В данном случае, это действие для поиска статуса и района.
 */
ScAddr StatusAndDistrictSearch::GetActionClass() const
{
  // Возвращаем соответствующий ключ для действия
  return Keynodes::action_statusAndDistrictSearch;
}

/*
 * Метод GetEventSubscriptionElement возвращает элемент, на который агент подписан.
 * В данном случае, это событие инициации действия.
 */
ScAddr StatusAndDistrictSearch::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

}  // namespace StatusAndDistrictSearchModule
