#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "keynodes/AdminKeynodes.hpp"

#include "GetAdminBuildingRegion.hpp"

using namespace adminModule;
using namespace utils;

SC_AGENT_IMPLEMENTATION(GetAdminBuildingRegion)
{
  ScAddr actionNode = m_memoryCtx.GetEdgeTarget(edgeAddr);

  if (!checkActionClass(actionNode))
  {
    return SC_RESULT_OK;
  }

  SC_LOG_DEBUG("GetAdminBuildingRegion started");

  ScAddr firstParameter =
      IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);

  if (!firstParameter.IsValid())
  {
    SC_LOG_ERROR("First parameter isn't valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr answerNode = m_memoryCtx.CreateNode(ScType::NodeConstStruct);
  ScAddr district;

  ScIterator5Ptr iterator5 = m_memoryCtx.Iterator5(
      ScType::Unknown,
      ScType::EdgeDCommonConst,
      firstParameter,
      ScType::EdgeAccessConstPosPerm,
      AdminKeynodes::nrel_region);
  while (iterator5->Next())
  {
    std::cout << "1 ";

    district = iterator5->Get(0);
    ScAddr building;

    ScIterator5Ptr it5 = m_memoryCtx.Iterator5(
        ScType::Unknown,
        ScType::EdgeDCommonConst,
        district,
        ScType::EdgeAccessConstPosPerm,
        AdminKeynodes::nrel_search_area);

    while (it5->Next())
    {
      std::cout << "2 ";
      building = it5->Get(0);

      if (m_memoryCtx.HelperCheckEdge(AdminKeynodes::concept_admin_building, building, ScType::EdgeAccessConstPosPerm))
        m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, answerNode, building);
    }
  }

  ScAddr edgeToAnswer = ms_context->CreateEdge(ScType::EdgeDCommonConst, actionNode, answerNode);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::nrel_answer, edgeToAnswer);

  AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, true);
  SC_LOG_DEBUG("GetAdminBuildingRegion finished");
  return SC_RESULT_OK;
}

bool GetAdminBuildingRegion::checkActionClass(const ScAddr & actionNode)
{
  return m_memoryCtx.HelperCheckEdge(
      AdminKeynodes::action_get_admin_building_region, actionNode, ScType::EdgeAccessConstPosPerm);
}
