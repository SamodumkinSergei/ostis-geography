#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "keynodes/AdminKeynodes.hpp"

#include "GetAdminBuildingDistrict.hpp"

using namespace adminModule;
using namespace utils;

SC_AGENT_IMPLEMENTATION(GetAdminBuildingDistrict)
{
  
  ScAddr actionNode = m_memoryCtx.GetEdgeTarget(edgeAddr); 

  if (!checkActionClass(actionNode)) 
  {
    return SC_RESULT_OK;
  }

  SC_LOG_DEBUG("GetAdminBuildingDistrict started");


  ScAddr firstParameter = IteratorUtils::getFirstByOutRelation(
        &m_memoryCtx,
        actionNode,
        scAgentsCommon::CoreKeynodes::rrel_1); 
  if (!firstParameter.IsValid())
  {
    SC_LOG_ERROR("First parameter isn't valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }


  ScAddr answerNode = m_memoryCtx.CreateNode(ScType::NodeConstStruct);
  
  ScAddr key_sc_element;
  
  ScIterator5Ptr iterator5 = m_memoryCtx.Iterator5(ScType::Unknown, ScType::EdgeDCommonConst,firstParameter , ScType::EdgeAccessConstPosPerm, AdminKeynodes::nrel_search_area);

  while (iterator5->Next())
  {
    key_sc_element = iterator5->Get(0);
   
  
    if (m_memoryCtx.HelperCheckEdge(AdminKeynodes::concept_admin_building, key_sc_element, ScType::EdgeAccessConstPosPerm))
         m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, answerNode, key_sc_element);

  }

  AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, answerNode, true);
  SC_LOG_DEBUG("GetAdminBuildingDistrict finished");
  return SC_RESULT_OK;
}

bool GetAdminBuildingDistrict::checkActionClass(const ScAddr & actionNode)
{
  return m_memoryCtx.HelperCheckEdge(
        AdminKeynodes::action_get_admin_building_district,
        actionNode,
        ScType::EdgeAccessConstPosPerm);
}

