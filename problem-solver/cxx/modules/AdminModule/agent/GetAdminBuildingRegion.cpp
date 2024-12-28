#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/AdminKeynodes.hpp"

#include "GetAdminBuildingRegion.hpp"

using namespace adminModule;
using namespace utils;


ScAddr GetAdminBuildingRegion::GetActionClass() const // Метод получения класса действия агента
{
  return AdminKeynodes::action_get_admin_building_region;
}

ScResult GetAdminBuildingRegion::DoProgram(ScAction & action) // Главный метод агента
{
  
  auto const & [first] = action.GetArguments<1>(); // Получение аргумента

  // Проверка наличия аргумента
  if (!m_context.IsElement(first))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  ScAddr answerNode = m_context.GenerateNode(ScType::NodeConstStructure); // Создание структуры ответа
  ScAddr district;

  ScIterator5Ptr iterator5 = m_context.CreateIterator5(
      ScType::Unknown,
      ScType::EdgeDCommonConst,
      first,
      ScType::EdgeAccessConstPosPerm,
      AdminKeynodes::nrel_region); // Итератор для поиска региона

  // Поиск региона
  while (iterator5->Next())
  {
    std::cout << "1 ";

    district = iterator5->Get(0);
    ScAddr building;

    ScIterator5Ptr it5 = m_context.CreateIterator5(
        ScType::Unknown,
        ScType::EdgeDCommonConst,
        district,
        ScType::EdgeAccessConstPosPerm,
        AdminKeynodes::nrel_search_area); // Итератор для поиска административных зданий

    // Поиск административных зданий
    while (it5->Next())
    {
      std::cout << "2 ";
      building = it5->Get(0);

      // Проверка на принадлежность к административным зданиям
      if (m_context.CheckConnector(AdminKeynodes::concept_admin_building, building, ScType::EdgeAccessConstPosPerm))
        m_context.GenerateConnector(ScType::EdgeAccessConstPosPerm, answerNode, building);
    }
  }

  action.SetResult(answerNode); // Привязка структуры ответа к агенту
  return action.FinishSuccessfully();
}


