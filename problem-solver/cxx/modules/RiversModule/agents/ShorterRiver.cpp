/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>

#include "ShorterRiver.hpp"
#include "keynodes/RiverKeynodes.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

ScAddr ShorterRiver::GetActionClass() const // Метод получения класса действия агента
{

  return RiverKeynodes::action_get_shorterRiver;
}


ScResult ShorterRiver::DoProgram(ScAction & action) // Главный метод агента
{
  auto const & [river1, river2] = action.GetArguments<2>();

  // Проверка наличия первого аргумента
  if (!m_context.IsElement(river1))
  {
    SC_AGENT_LOG_ERROR("Action does not have first argument.");
    return action.FinishWithError();
  }

  // Проверка наличия второго аргумента
  if (!m_context.IsElement(river2))
  {
    SC_AGENT_LOG_ERROR("Action does not have second argument.");
    return action.FinishWithError();
  }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it = m_context.CreateIterator5(
      river1, ScType::ConstCommonArc, 
      ScType::Unknown, 
      ScType::ConstPermPosArc, 
      RiverKeynodes::nrel_length); // Итератор для поиска длины первой реки
  int l1 = 0;

  //Поиск длины первой реки 
  while (it->Next())
  {
    ScAddr len = it->Get(2);
    std::string str1 = CommonUtils::getIdtf(&m_context, len, ScKeynodes::nrel_main_idtf);
    l1 = std::atoi(str1.c_str());
  }

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      river2, ScType::ConstCommonArc, 
      ScType::Unknown, 
      ScType::ConstPermPosArc, 
      RiverKeynodes::nrel_length); // Итератор для поиска длины второй реки
  int l2 = 0;

  // Поиск длины второй реки
  while (it1->Next())
  {
    ScAddr len = it1->Get(2);
    std::string str2 = CommonUtils::getIdtf(&m_context, len, ScKeynodes::nrel_main_idtf);
    l2 = std::atoi(str2.c_str());
  }

  
  if (l1 < l2)
  {
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        river1, ScType::Unknown, 
        ScType::Unknown, 
        ScType::ConstPermPosArc, 
        RiverKeynodes::nrel_length); // Итератор для обхода всех знаний о первой реке

    if (iteratorToAddToAnswer->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  else
  {
    ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
        river2, ScType::Unknown, 
        ScType::Unknown, 
        ScType::ConstPermPosArc, 
        RiverKeynodes::nrel_length); // Итератор для обхода всех знаний о второй реке


    if (iteratorToAddToAnswer->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
    }
  }
  
  action.SetResult(answer); // Привязка структуры ответа к агенту
  return action.FinishSuccessfully();
}






}  
