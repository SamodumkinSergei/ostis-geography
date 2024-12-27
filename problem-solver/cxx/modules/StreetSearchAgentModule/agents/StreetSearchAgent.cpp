#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-memory/sc_memory.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "StreetSearchAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace StreetSearchAgentModule
{

/* 
 * Метод DoProgram выполняет основную логику агента, который реагирует на событие 
 * создания исходящей дуги (ScEventAfterGenerateOutgoingArc). Агент ищет улицу, 
 * связанную с заданным параметром, и проверяет наличие площади поиска для этой улицы.
 */
ScResult StreetSearchAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  // Проверка на валидность дуги события. Если она невалидна, завершаем агент с ошибкой
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("begin");

  // Получаем целевой узел дуги, который является элементом действия
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  // Используем утилиту для получения улицы, связанной с данным действием
  ScAddr street = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);

  // Проверяем, найдена ли улица. Если улица не найдена, завершаем агент с ошибкой
  if (!street.IsValid())
  {
    SC_AGENT_LOG_ERROR("First parameter isn't valid.");
    // Можно заменить использование AgentUtils (комментарий "todo")
    return action.FinishUnsuccessfully();
  }

  // Создаем узел, в котором будет храниться результат
  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  // Создаем итератор для поиска длины улицы через отношение nrel_street_length
  ScIterator5Ptr it1 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, street, ScType::ConstPermPosArc, Keynodes::nrel_street_length);
  
  ScAddr street1;
  ScAddr streetResult;

  // Если длина улицы найдена, продолжаем искать площадь поиска
  if (it1->Next())
  {
    street = it1->Get(0);

    // Создаем второй итератор для поиска площади поиска через отношение nrel_search_area
    ScIterator5Ptr it2 = m_context.CreateIterator5(
        street, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_search_area);
    
    // Если площадь поиска найдена, добавляем связь между результатом и улицей
    if (it2->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, streetResult);
    }
    else
    {
      // Если площадь поиска не найдена, выводим сообщение об ошибке
      SC_AGENT_LOG_ERROR("There is no such street");
    }
  }

  // Создаем соединение между результатом и узлом действия
  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  
  // Устанавливаем результат действия
  action.SetResult(answer);
  SC_AGENT_LOG_INFO("end");

  // Завершаем выполнение действия с успешным результатом
  return action.FinishSuccessfully();
}

/*
 * Метод GetActionClass возвращает класс действия, с которым работает агент.
 * В данном случае, это действие для поиска улиц по длине.
 */
ScAddr StreetSearchAgent::GetActionClass() const
{
  // Возвращаем соответствующий ключ для действия
  return Keynodes::action_streetByLenghtSearch;
}

/*
 * Метод GetEventSubscriptionElement возвращает элемент, на который агент подписан.
 * В данном случае, это событие инициации действия.
 */
ScAddr StreetSearchAgent::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

}  // namespace StreetSearchAgentModule
