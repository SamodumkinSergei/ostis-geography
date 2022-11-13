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

#include "TrashByCount.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace TrashModule {

        SC_AGENT_IMPLEMENTATION(TrashByCount)
	{
		if (!edgeAddr.IsValid())
			return SC_RESULT_ERROR;


		SC_LOG_INFO("----------TrashByCount begin----------");
		ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
		ScAddr number = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
		if (!number.IsValid())
			return SC_RESULT_ERROR_INVALID_PARAMS;
		ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);




		ScIterator5Ptr it = ms_context->Iterator5(ScType::Unknown, ScType::EdgeDCommonConst,number, ScType::EdgeAccessConstPosPerm,Keynodes::nrel_number_of_stocked_pesticides);
ScAddr smth;
		while (it->Next())
			{
				smth = it->Get(0);

ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, smth);
string str = CommonUtils::getIdtfValue(ms_context.get(), number,Keynodes::nrel_number_of_stocked_pesticides);
SC_LOG_INFO(str);
	}		

		SC_LOG_INFO("----------TrashByCount end----------");
		AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
		return SC_RESULT_OK;
	}
}
