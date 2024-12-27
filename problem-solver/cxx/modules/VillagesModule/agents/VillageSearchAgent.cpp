/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <sc-memory/sc_stream.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/GenerationUtils.hpp>
#include"sc-memory/sc_memory.hpp"
#include <iostream>
#include "VillageSearchAgent.hpp"

using namespace std;
using namespace utils;

namespace VillagesModule
{

/*
 * Функция getVillageNode ищет деревню в Витебской области среди элементов, 
 * которые связаны с данным множеством. Она использует итератор для поиска 
 * деревни через отношение "nrel_Vitebsk_village".
 */
ScAddr getVillageNode(ScLog * logger, std::unique_ptr<ScMemoryContext> & ms_context, ScAddr set)
{
  // Создаем новый узел для хранения ответа
  ScAddr answer = ms_context->GenerateNode(ScType::ConstNodeStructure);

  // Ищем элемент, соответствующий Витебской деревне
  ScAddr first = ms_context->SearchElementBySystemIdentifier("nrel_Vitebsk_village");
  logger->Message(ScLog::Type::Info, "Villages Vitebsk " + ms_context->GetElementSystemIdentifier(set));

  // Создаем итератор для поиска по отношению "nrel_Vitebsk_village"
  ScIterator5Ptr iter =
      ms_context->CreateIterator5(set, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, first);
  
  // Пробегаем по всем найденным элементам
  while (iter->Next())
  {
    SC_LOG_ERROR("Found Vitebsk village");
    // Логируем найденную деревню
    logger->Message(ScLog::Type::Info, "Village: " + ms_context->GetElementSystemIdentifier(iter->Get(2)));
    // Добавляем найденную деревню к ответу
    ms_context->GenerateConnector(ScType::ConstPermPosArc, answer, iter->Get(2));
    return answer;  // Возвращаем найденный результат
  }
  // Если деревня не найдена, выводим лог
  logger->Message(ScLog::Type::Info, "village not found");

  // Возвращаем пустой ответ, если деревня не найдена
  return answer;
}

/*
 * Метод DoProgram реализует логику агента, который обрабатывает событие 
 * создания исходящей дуги (ScEventAfterGenerateOutgoingArc). Агент ищет деревню 
 * в Витебской области и возвращает результат.
 */
ScResult VillageSearchAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  // Создаем контекст памяти для агента
  ScAgentContext ms_context;
  SC_AGENT_LOG_ERROR("started");

  // Получаем логгер для записи информации
  ScLog * logger = ScLog::GetInstance();

  // Проверка на валидность дуги, если она невалидна — завершаем выполнение с ошибкой
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  // Получаем целевой узел действия
  ScAddr questionNode = ms_context.GetArcTargetElement(event.GetArc());

  // Ищем узел, связанный с данным вопросом
  ScAddr node = IteratorUtils::getAnyFromSet(&ms_context, questionNode);
  if (!node.IsValid())
  {
    SC_AGENT_LOG_ERROR("Arg not found");
    return action.FinishUnsuccessfully();  // Если узел не найден, завершаем с ошибкой
  }

  // Получаем ответ на запрос, вызвав функцию поиска деревни
  std::unique_ptr<ScMemoryContext> context;
  ScAddr answer = getVillageNode(logger, context, node);

  // Создаем соединение между вопросом и ответом
  ScAddr edgeToAnswer = ms_context.GenerateConnector(ScType::ConstCommonArc, questionNode, answer);
  
  // Устанавливаем результат действия
  action.SetResult(answer);

  // Завершаем выполнение действия с успешным результатом
  return action.FinishSuccessfully();
}

/*
 * Метод GetActionClass возвращает класс действия, с которым работает агент.
 * В данном случае, это действие для поиска деревни в Витебской области.
 */
ScAddr VillageSearchAgent::GetActionClass() const
{
  // Возвращаем соответствующий ключ для действия
  return Keynodes::question_vitebskVillage;
}

/*
 * Метод GetEventSubscriptionElement возвращает элемент, на который агент подписан.
 * В данном случае, это событие инициации действия.
 */
ScAddr VillageSearchAgent::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

}  // namespace VillagesModule
