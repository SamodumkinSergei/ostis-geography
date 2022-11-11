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

#include "LibrariesTownSearch.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace LibrariesTownSearchModule {

	SC_AGENT_IMPLEMENTATION(LibrariesTownSearch)
	{
        ScAddr actionNode = m_memoryCtx.GetEdgeTarget(edgeAddr);

		if (!edgeAddr.IsValid())
			return SC_RESULT_ERROR;


		SC_LOG_INFO("Libraries town search begin");

        ScAddr library = IteratorUtils::getFirstByOutRelation(
            &m_memoryCtx,
            actionNode,
            scAgentsCommon::CoreKeynodes::rrel_1); 

        if (!library.IsValid())
        {
            SC_LOG_ERROR("Parameter isn't valid.")
                AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
            return SC_RESULT_ERROR_INVALID_PARAMS;
        }

        ScAddr libraryResult = m_memoryCtx.CreateNode(ScType::NodeConstStruct);
        m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, libraryResult, library); 

        ScAddr key_sc_element;

        ScIterator5Ptr iterator5 = m_memoryCtx.Iterator5(ScType::Unknown, ScType::EdgeAccessConstPosPerm, library, ScType::EdgeAccessConstPosPerm, ExampleKeynodes::nrel_city);
        while (iterator5->Next()) {
            key_sc_element = iterator5->Get(0);
            m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, libraryResult, iterator5->Get(2));
        }

        AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, libraryResult, true);
        SC_LOG_DEBUG("Libraries town search finished")
            return SC_RESULT_OK;
    }
	
}
