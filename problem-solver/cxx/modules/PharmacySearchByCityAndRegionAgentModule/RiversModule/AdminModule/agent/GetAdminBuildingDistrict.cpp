#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "keynodes/AdminKeynodes.hpp"

#include "GetAdminBuildingDistrict.hpp"

using namespace adminModule;
using namespace utils;


ScAddr GetAdminBuildingDistrict::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return AdminKeynodes::action_get_admin_building_district; 
  // return m_context.SearchElementBySystemIdentifier("action_get_admin_building_district");
}

// ScResult GetAdminBuildingDistrict::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) const 
ScResult GetAdminBuildingDistrict::DoProgram(ScAction & action) 
{
  auto const & [first] = action.GetArguments<1>();

  if (!m_context.IsElement(first))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  ScAddr answerNode = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScAddr key_sc_element;

  ScIterator5Ptr iterator5 = m_context.CreateIterator5(
      ScType::Unknown,
      ScType::ConstCommonArc,
      first,
      ScType::ConstPermPosArc,
      AdminKeynodes::nrel_search_area);

  while (iterator5->Next())
  {
    key_sc_element = iterator5->Get(0);

    if (m_context.CheckConnector(
            AdminKeynodes::concept_admin_building, key_sc_element, ScType::ConstPermPosArc));
      m_context.GenerateConnector(ScType::ConstPermPosArc, answerNode, key_sc_element);
  }

  action.SetResult(answerNode);
  return action.FinishSuccessfully();
}

// ScAddr GetAdminBuildingDistrict::GetEventSubscriptionElement() const
// {
//   return ScKeynodes::action_initiated;
// }

// bool GetAdminBuildingDistrict::checkActionClass(const ScAddr & actionNode) const
// {
//   return m_context.CheckConnector(
//       AdminKeynodes::action_get_admin_building_district, actionNode, ScType::ConstPermPosArc);
// }
