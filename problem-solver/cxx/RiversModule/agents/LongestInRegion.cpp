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



ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);


ScIterator5Ptr it1 = ms_context->Iterator5(ScType::Unknown, ScType::EdgeDCommonConst,region, ScType::EdgeAccessConstPosPerm,Keynodes::nrel_region);
ScAddr river;
int number=0;
ScAddr riv;
while (it1->Next())
{
river = it1->Get(0);
ScIterator5Ptr it2 = ms_context->Iterator5(river, ScType::EdgeDCommonConst,ScType::Unknown, ScType::EdgeAccessConstPosPerm,Keynodes::nrel_length);
while(it2->Next())
{
ScAddr num = it2->Get(2);
std::string str = CommonUtils::getIdtfValue(ms_context.get(), num, Keynodes::nrel_main_idtf);
SC_LOG_INFO(str.c_str());
int n = std::atoi(str.c_str());
if(number<n)
{
number = n;
riv = river;
}
}
}
		ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, riv);
		SC_LOG_INFO("----------LongestInRegion end----------");
		AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
		return SC_RESULT_OK;
	}
}
