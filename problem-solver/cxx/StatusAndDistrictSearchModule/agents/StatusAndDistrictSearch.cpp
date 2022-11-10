/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "StatusAndDistrictSearch.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace StatusAndDistrictSearchModule {

	SC_AGENT_IMPLEMENTATION(StatusAndDistrictSearch)
	{
		if (!edgeAddr.IsValid())
			return SC_RESULT_ERROR;


		SC_LOG_INFO("StatusAndDistrictSearch begin");
		ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

		ScAddr shop = IteratorUtils::getFirstByOutRelation(
			&m_memoryCtx,
			actionNode,
			scAgentsCommon::CoreKeynodes::rrel_1);

		if (!firstParameter.IsValid())
		{
			SC_LOG_ERROR("First parameter isn't valid.")
				AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
			return SC_RESULT_ERROR_INVALID_PARAMS;
		}

		ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);


		ScIterator5Ptr it1 = ms_context->Iterator5(ScType::Unknown, ScType::EdgeDCommonConst, shop, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_district);
		ScAddr shop1;
		ScAddr shopResult;
		if (it1->Next())
		{
			shop = it1->Get(0);
			ScIterator5Ptr it2 = ms_context->Iterator5(shop, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_status);
			if (it2->Next())
			{
				ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, shopResult);
			}
			else {
				SC_LOG_ERROR("There is no such embassy in Minsk")
			}
		}
		AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
		SC_LOG_INFO("StatusAndDistrictSearch end");
		return SC_RESULT_OK;
	}	
	
}
