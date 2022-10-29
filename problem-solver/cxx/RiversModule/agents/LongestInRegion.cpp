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

#include "LongestInRegion.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace RiversModule {

	SC_AGENT_IMPLEMENTATION(LongestInRegion)
	{
		if (!edgeAddr.IsValid())
			return SC_RESULT_ERROR;


		SC_LOG_INFO("----------LongestInRegion begin----------");
		ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

		ScAddr region = IteratorUtils::getFirstByOutRelation(
			&m_memoryCtx,
			actionNode,
			scAgentsCommon::CoreKeynodes::rrel_1);

		if (!region.IsValid()) {
			SC_LOG_INFO("region is not valid");
			return SC_RESULT_ERROR;
		}

		std::string regionIdtf = CommonUtils::getIdtfValue(ms_context.get(), region, Keynodes::nrel_main_idtf);
		SC_LOG_INFO("region is " + regionIdtf);


		ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);


		ScIterator5Ptr it1 = ms_context->Iterator5(ScType::Unknown, ScType::EdgeDCommonConst, region, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_region);
		ScAddr river{};
		int number = 0;
		ScAddr riv;
		while (it1->Next())
		{
			river = it1->Get(0);
			ScIterator5Ptr it2 = ms_context->Iterator5(river, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_length);
			while (it2->Next())
			{
				ScAddr num = it2->Get(2);
				std::string str = CommonUtils::getIdtfValue(ms_context.get(), num, Keynodes::nrel_main_idtf);
				SC_LOG_INFO(str.c_str());
				int n = std::atoi(str.c_str());
				if (number < n)
				{
					number = n;
					riv = river;
				}
			}
		}
		if (riv.IsValid()) {
			std::string riverName = CommonUtils::getIdtfValue(ms_context.get(), riv, Keynodes::nrel_main_idtf);
			SC_LOG_INFO("longest river in " + regionIdtf + " is " + riverName);

			ScIterator5Ptr iteratorToAddToAnswer = ms_context->Iterator5(riv, ScType::Unknown, region, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_region);
			if (iteratorToAddToAnswer->Next()) {
				ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(0));
				ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(1));
				ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(2));
				ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(3));
				ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iteratorToAddToAnswer->Get(4));
			}
		}

		SC_LOG_INFO("----------LongestInRegion end----------");
		AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
		return SC_RESULT_OK;
	}
}
