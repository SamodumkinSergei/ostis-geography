/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "PotteryDate.hpp"
#include "keynodes/PotteryKeynodes.hpp"

using namespace std;
using namespace utils;

namespace PotteryModule
{

ScAddr PotteryDate::GetActionClass() const // Метод получения класса действия агента
{
  return PotteryKeynodes::action_get_pottery;
}


ScResult PotteryDate::DoProgram(ScAction & action) // Гланый метод агента
{
  auto const & [date1, date2] = action.GetArguments<2>();

  // Проверка наличия первого аргумента
  if (!m_context.IsElement(date1))
  {
    SC_AGENT_LOG_ERROR("Action does not have first argument.");

    return action.FinishWithError();
  }

  // Проверка наличия второго аргумента
  if (!m_context.IsElement(date2))
  {
    SC_AGENT_LOG_ERROR("Action does not have second argument.");

    return action.FinishWithError();
  }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  std::string str1 = CommonUtils::getIdtf(&m_context, date1, ScKeynodes::nrel_main_idtf);
  std::string str2 = CommonUtils::getIdtf(&m_context, date2, ScKeynodes::nrel_main_idtf);
  
  
  int d1 = std::atoi(str1.c_str());
  int d2 = std::atoi(str2.c_str());

  ScIterator3Ptr it2 = m_context.CreateIterator3(
      PotteryKeynodes::pottery_centre, 
      ScType::ConstPermPosArc, 
      ScType::Unknown); // Итератор для поиска предприятий по производству керамики 
  ScAddr smth;

  // Поиск предприятий по производству керамики
  while (it2->Next())
  {

    smth = it2->Get(2);
    ScIterator5Ptr it1 = m_context.CreateIterator5(
        smth, ScType::ConstCommonArc, 
        ScType::Unknown, 
        ScType::ConstPermPosArc, 
        PotteryKeynodes::nrel_date); // Итератор для поска даты
    ScAddr date;

    // Поиск даты
    while (it1->Next())
    {
      date = it1->Get(2);
      std::string str = CommonUtils::getIdtf(&m_context, date, ScKeynodes::nrel_main_idtf);
      
      int d = std::atoi(str.c_str());
      if (d < d2)
      {
        if (d > d1)
        {
          m_context.GenerateConnector(ScType::ConstPermPosArc, answer, smth);
        }
      }
    }
  }

  

  
  action.SetResult(answer); // Привязка структуры агента к агенту
  return action.FinishSuccessfully();
}







}  
