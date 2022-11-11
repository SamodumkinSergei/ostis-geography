#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "PharmacySearchByCityAndRegionAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace PharmacySearchByCityAndRegionAgentModule {

SC_AGENT_IMPLEMENTATION(PharmacySearchByCityAndRegionAgent)
	{
		if (!edgeAddr.IsValid())
			return SC_RESULT_ERROR;


		SC_LOG_INFO("PharmacySearchByCityAndRegionAgent begin");
		ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

		ScAddr pharmacy = IteratorUtils::getFirstByOutRelation(
			&m_memoryCtx,
			actionNode,
			scAgentsCommon::CoreKeynodes::rrel_1);

		if (!street.IsValid())
		{
			SC_LOG_ERROR("First parameter isn't valid.");
				AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
			return SC_RESULT_ERROR_INVALID_PARAMS;
		}

		ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);


		ScIterator5Ptr it1 = ms_context->Iterator5(ScType::Unknown, ScType::EdgeDCommonConst, pharmacy, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_city);
		ScAddr pharmacy1;
		ScAddr pharmacyResult;
		if (it1->Next())
		{
            pharmacy = it1->Get(0);
			ScIterator5Ptr it2 = ms_context->Iterator5(pharmacy, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_region);
			if (it2->Next())
			{
				ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, pharmacyResult);
			}
			else {
				SC_LOG_ERROR("There is no such pharmacy");
			}
		};
		AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
		SC_LOG_INFO("PharmacySearchByCityAndRegionAgent end");
		return SC_RESULT_OK;
	}	

}
