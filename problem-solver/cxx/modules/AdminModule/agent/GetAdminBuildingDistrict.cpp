#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "keynodes/AdminKeynodes.hpp"

#include "GetAdminBuildingDistrict.hpp"

using namespace adminModule;
using namespace utils;


ScAddr GetAdminBuildingDistrict::GetActionClass() const // Метод получения класса действия агента
{
  return AdminKeynodes::action_get_admin_building_district; 
}

ScResult GetAdminBuildingDistrict::DoProgram(ScAction & action) // Главный метод агента
{
  auto const & [first] = action.GetArguments<1>(); // Получение аргумента

  // Проверка наличия аргумента
  if (!m_context.IsElement(first))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  ScAddr answerNode = m_context.GenerateNode(ScType::ConstNodeStructure); // Создание структуры ответа  

  ScAddr key_sc_element;

  ScIterator5Ptr iterator5 = m_context.CreateIterator5(
      ScType::Unknown,
      ScType::ConstCommonArc,
      first,
      ScType::ConstPermPosArc,
      AdminKeynodes::nrel_search_area); // Итератор для поиска района

  // Поиск района
  while (iterator5->Next())
  {
    key_sc_element = iterator5->Get(0);

    // Проверка принадлежности к району
    if (m_context.CheckConnector(AdminKeynodes::concept_admin_building, key_sc_element, ScType::ConstPermPosArc));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answerNode, key_sc_element);
  }

  action.SetResult(answerNode); // Привязка структуры ответа к агенту
  return action.FinishSuccessfully();
}
