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

#include "GreatestDistanceToTheRegionalCenter.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace VitebskVillagesModule
{

/*
 * Основная логика агента. Агент получает две деревни и находит расстояние до 
 * регионального центра для каждой из них, а затем выбирает наибольшее расстояние.
 */
ScResult GreatestDistanceToTheRegionalCenter::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  // Проверка валидности дуги. Если она невалидна, завершаем с ошибкой
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("----------Greatest Distance To The Regional Center begin agent----------");

  // Получаем целевой узел действия (узел, который инициировал событие)
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  // Извлекаем деревни, используя их связи с текущим узлом
  ScAddr village1 = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);
  ScAddr village2 = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_2);

  // Создаем узел для хранения результата
  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  // Поиск расстояния от первой деревни до регионального центра
  ScIterator5Ptr it = m_context.CreateIterator5(
      village1,
      ScType::ConstCommonArc,
      ScType::Unknown,
      ScType::ConstPermPosArc,
      Keynodes::nrel_distanceFromArea);
  int l1 = 0; // Переменная для хранения расстояния для первой деревни
  while (it->Next())
  {
    // Получаем и конвертируем строковое значение расстояния в число
    ScAddr len = it->Get(2);
    std::string str1 = CommonUtils::getIdtf(&m_context, len, Keynodes::nrel_main_idtf);
    l1 = std::atoi(str1.c_str());
    SC_AGENT_LOG_INFO(str1);  // Логируем значение расстояния для первой деревни
  }

  // Поиск расстояния от второй деревни до регионального центра
  ScIterator5Ptr it1 = m_context.CreateIterator5(
      village2,
      ScType::ConstCommonArc,
      ScType::Unknown,
      ScType::ConstPermPosArc,
      Keynodes::nrel_distanceFromArea);
  int l2 = 0; // Переменная для хранения расстояния для второй деревни
  while (it1->Next())
  {
    // Получаем и конвертируем строковое значение расстояния во втором случае
    ScAddr len = it1->Get(2);
    std::string str2 = CommonUtils::getIdtf(&m_context, len, Keynodes::nrel_main_idtf);
    l2 = std::atoi(str2.c_str());
    SC_AGENT_LOG_INFO(str2);  // Логируем значение расстояния для второй деревни
  }

  // Сравниваем расстояния и выбираем наибольшее
  if (l1 > l2)
  {
    // Если первое расстояние больше, выбираем данные для первой деревни
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        village1, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_distanceFromArea);

    if (iteratorToAddToAnswer->Next())
    {
      // Добавляем данные расстояния в ответ
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  else
  {
    // Если второе расстояние больше, выбираем данные для второй деревни
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        village2, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_distanceFromArea);

    if (iteratorToAddToAnswer->Next())
    {
      // Добавляем данные расстояния в ответ
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }

  // Создаем соединение между исходным узлом действия и результатом
  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  m_context.GenerateConnector(ScType::ConstPermPosArc, ScKeynodes::nrel_result, edgeToAnswer);

  SC_AGENT_LOG_INFO("----------GreatestDistanceToTheRegionalCenter end agent----------");

  // Устанавливаем результат действия
  action.SetResult(answer);

  // Завершаем выполнение успешно
  return action.FinishSuccessfully();
}

/*
 * Возвращает класс действия для агента.
 */
ScAddr GreatestDistanceToTheRegionalCenter::GetActionClass() const
{
  // Возвращаем ключ для действия, которое ищет наибольшее расстояние до регионального центра
  return Keynodes::question_greatestDistanceToTheRegionalCenter;
}

/*
 * Возвращает элемент, на который подписан агент.
 */
ScAddr GreatestDistanceToTheRegionalCenter::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

}  // namespace VitebskVillagesModule
