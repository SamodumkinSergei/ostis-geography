/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>

#include "LongestInRegion.hpp"

using namespace std;
using namespace utils;

namespace RiversModule
{

ScAddr LongestInRegion::GetActionClass() const // Метод получения класса действия агента
{ 

  return RiverKeynodes::action_get_longestInRegion;
}


ScResult LongestInRegion::DoProgram(ScAction & action) // Главный метод агента
{  
  auto const & [region] = action.GetArguments<1>();

  // Проверка наличия аргумента  
  if (!m_context.IsElement(region))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }  

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  int maxLength = 0;
  ScAddr longestRiverAddr;

  auto iteratorForRivers = m_context.CreateIterator5(
      ScType::Unknown, 
      ScType::ConstCommonArc, 
      region, ScType::ConstPermPosArc, 
      RiverKeynodes::nrel_region); // Итератор для поиска рек

  // Поиск рек
  while (iteratorForRivers->Next())
  {
    ScAddr riverAddr = iteratorForRivers->Get(0);
    std::string riverName = CommonUtils::getIdtf(&m_context, riverAddr, ScKeynodes::nrel_main_idtf);
    auto iteratorForLength = m_context.CreateIterator5(
        riverAddr, ScType::ConstCommonArc, 
        ScType::Unknown, 
        ScType::ConstPermPosArc, 
        RiverKeynodes::nrel_length); // Итератор для поиска длин областных рек 

    // Поиск длин областных рек 
    while (iteratorForLength->Next())
    {
      ScAddr lengthAddr = iteratorForLength->Get(2);
      std::string lengthStr = CommonUtils::getIdtf(&m_context, lengthAddr, ScKeynodes::nrel_main_idtf);
      
      int lengthInt = std::stoi(lengthStr.c_str());

      // Проверка длиннее ли найденная река записанной длины 
      if (maxLength < lengthInt)
      {
        maxLength = lengthInt;
        longestRiverAddr = riverAddr;
      }
    }
  }
  
  ScIterator5Ptr iteratorToAddToAnswer = m_context.CreateIterator5(
      longestRiverAddr, ScType::Unknown, 
      ScType::Unknown, 
      ScType::ConstPermPosArc, 
      RiverKeynodes::nrel_length); // Итератор для обхода всех знаний самой длинной областной реки

  if (iteratorToAddToAnswer->Next())
  {
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(0));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(1));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(2));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(3));
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, iteratorToAddToAnswer->Get(4));
  }
  

  action.SetResult(answer); // Привязка структуры ответа 
  return action.FinishSuccessfully();
}

}  
