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

#include "LargerVillageByPopulationInTheDistrict.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace VitebskVillagesModule
{

// Реализация программы для поиска самого крупного по населению поселения в районе
ScResult LargerVillageByPopulationInTheDistrict::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  // Создаем контекст агента
  ScAgentContext ms_context;
  
  // Проверяем, что дуга валидна, если нет, завершаем выполнение с ошибкой
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("----------LargerVillageByPopulationInTheDistrict begin----------");

  // Получаем узел действия, к которому привязана дуга
  ScAddr actionNode = ms_context.GetArcTargetElement(event.GetArc());

  // Извлекаем район из отношения rrel_1
  ScAddr district =
      IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);

  // Если район не найден, выводим ошибку и завершаем выполнение
  if (!district.IsValid())
  {
    SC_AGENT_LOG_ERROR("District is not valid");
    return action.FinishUnsuccessfully();
  }

  // Создаем узел для хранения ответа
  ScAddr answer = ms_context.GenerateNode(ScType::ConstNodeStructure);

  // Создаем итератор для поиска всех поселений, связанных с данным районом
  ScIterator5Ptr it1 = ms_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, district, ScType::ConstPermPosArc, Keynodes::nrel_district);
  ScAddr village;
  int number = 0;
  ScAddr largestVillage{};  // Переменная для хранения поселения с наибольшим населением

  // Перебираем все поселения в районе
  while (it1->Next())
  {
    village = it1->Get(0);  // Получаем поселение

    // Для каждого поселения находим его население
    ScIterator5Ptr it2 = ms_context.CreateIterator5(
        village, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, Keynodes::nrel_population);
    while (it2->Next())
    {
      ScAddr num = it2->Get(2);  // Получаем количество населения
      std::string str = CommonUtils::getIdtf(&ms_context, num, Keynodes::nrel_main_idtf);  // Преобразуем в строку
      SC_AGENT_LOG_INFO(str.c_str());  // Логируем население
      int n = std::atoi(str.c_str());  // Преобразуем строку в число

      // Сравниваем население текущего поселения с максимальным
      if (number < n)
      {
        number = n;
        largestVillage = village;  // Обновляем самое крупное поселение
      }
    }
  }

  // Если найдено поселение с максимальным населением, добавляем его в ответ
  if (largestVillage.IsValid())
  {
    ScIterator5Ptr iteratorToAddToAnswer = ms_context.CreateIterator5(
        largestVillage, ScType::Unknown, district, ScType::ConstPermPosArc, Keynodes::nrel_district);

    if (iteratorToAddToAnswer->Next())
    {
      // Генерируем соединители для ответа
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      ms_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  else
  {
    // Если не найдено самое крупное поселение, выводим предупреждение
    SC_AGENT_LOG_WARNING("There is no largest village in this district");
  }

  // Создаем соединитель для связи действия с результатом
  ScAddr edgeToAnswer = ms_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  ms_context.GenerateConnector(ScType::ConstPermPosArc, ScKeynodes::nrel_result, edgeToAnswer);

  SC_AGENT_LOG_INFO("----------LargerVillageByPopulationInTheDistrict end----------");
  
  // Устанавливаем результат действия и завершаем выполнение с успехом
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

// Возвращает класс действия
ScAddr LargerVillageByPopulationInTheDistrict::GetActionClass() const
{
  // todo(codegen-removal): заменить action на ваш класс действия
  return Keynodes::question_largerVillageByPopulationInTheDistrict;
}

// Возвращает элемент подписки на событие
ScAddr LargerVillageByPopulationInTheDistrict::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

}  // namespace VitebskVillagesModule
