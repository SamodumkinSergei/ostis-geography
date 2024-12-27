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

#include "LargerVillageByPopulation.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace VitebskVillagesModule
{

/*
 * Основная логика агента. Агент получает два поселения, сравнивает их население
 * и определяет, какое из них имеет большее население.
 */
ScResult LargerVillageByPopulation::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  // Проверяем, если дуга невалидна, завершаем неудачно
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("----------LargerVillageByPopulation start----------");

  // Извлекаем узел действия, который вызвал это событие
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  // Извлекаем два поселения через их отношения с текущим узлом действия
  ScAddr village1 = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);
  ScAddr village2 = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_2);

  // Создаем узел для хранения ответа
  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  // Ищем население первого поселения
  ScIterator5Ptr it = m_context.CreateIterator5(
      village1, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);
  int l1 = 0; // Переменная для хранения населения первого поселения
  while (it->Next())
  {
    // Получаем и конвертируем значение населения в целое число
    ScAddr len = it->Get(2);
    std::string str1 = CommonUtils::getIdtf(&m_context, len, Keynodes::nrel_main_idtf);
    l1 = std::atoi(str1.c_str());
    SC_AGENT_LOG_INFO(str1);  // Логируем население первого поселения
  }

  // Ищем население второго поселения
  ScIterator5Ptr it1 = m_context.CreateIterator5(
      village2, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);
  int l2 = 0; // Переменная для хранения населения второго поселения
  while (it1->Next())
  {
    // Получаем и конвертируем значение населения второго поселения
    ScAddr len = it1->Get(2);
    std::string str2 = CommonUtils::getIdtf(&m_context, len, Keynodes::nrel_main_idtf);
    l2 = std::atoi(str2.c_str());
    SC_AGENT_LOG_INFO(str2);  // Логируем население второго поселения
  }

  // Сравниваем населения двух поселений
  if (l1 > l2)
  {
    // Если первое поселение имеет большее население, добавляем его данные в ответ
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        village1, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);

    if (iteratorToAddToAnswer->Next())
    {
      // Генерируем соединители для добавления данных о первом поселении в ответ
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  else
  {
    // Если второе поселение имеет большее население, добавляем его данные в ответ
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        village2, ScType::Unknown, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);

    if (iteratorToAddToAnswer->Next())
    {
      // Генерируем соединители для добавления данных о втором поселении в ответ
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }

  // Создаем соединитель между узлом действия и ответом
  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  // Генерируем соединитель с результатом
  m_context.GenerateConnector(ScType::ConstPermPosArc, ScKeynodes::nrel_result, edgeToAnswer);

  SC_AGENT_LOG_INFO("----------LargerVillageByPopulation end----------");
  
  // Устанавливаем результат действия
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

// Получаем класс действия для агента
ScAddr LargerVillageByPopulation::GetActionClass() const
{
  return Keynodes::question_largerVillageByPopulation;
}

// Получаем элемент подписки на событие
ScAddr LargerVillageByPopulation::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

}  // namespace VitebskVillagesModule
