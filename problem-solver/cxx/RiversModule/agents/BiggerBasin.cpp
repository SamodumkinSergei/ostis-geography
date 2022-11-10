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

#include "BiggerBasin.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace RiversModule {

        SC_AGENT_IMPLEMENTATION(BiggerBasin)
	{
		if (!edgeAddr.IsValid())
			return SC_RESULT_ERROR;


		SC_LOG_INFO("----------BiggerBasin begin----------");
		ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

ScAddr river1 = IteratorUtils::getFirstByOutRelation(
        &m_memoryCtx,
        actionNode,
        scAgentsCommon::CoreKeynodes::rrel_1); 

ScAddr river2 = IteratorUtils::getFirstByOutRelation(
        &m_memoryCtx,
        actionNode,
        scAgentsCommon::CoreKeynodes::rrel_2);
ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);


ScIterator5Ptr it = ms_context->Iterator5(river1, ScType::EdgeDCommonConst,ScType::Unknown, ScType::EdgeAccessConstPosPerm,Keynodes::nrel_basin);
int l1=0;
while (it->Next())
{
ScAddr len = it->Get(2);
std::string str1 = CommonUtils::getIdtfValue(ms_context.get(), len, Keynodes::nrel_main_idtf);
l1 = std::atoi(str1.c_str());
}

ScIterator5Ptr it1 = ms_context->Iterator5(river2, ScType::EdgeDCommonConst,ScType::Unknown, ScType::EdgeAccessConstPosPerm,Keynodes::nrel_basin);
int l2=0;
while (it1->Next())
{
ScAddr len = it1->Get(2);
std::string str2 = CommonUtils::getIdtfValue(ms_context.get(), len, Keynodes::nrel_main_idtf);
l2 = std::atoi(str2.c_str());
}

if(l1>l2)
{
ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, river1);
}
else
{
ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, river2);
}

		
		SC_LOG_INFO("----------BiggerBasin end----------");
		AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
		return SC_RESULT_OK;
	}
}
