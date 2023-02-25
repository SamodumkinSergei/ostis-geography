/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "RiverFlowSearchAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace RiverFlowSearchAgentModule
{

    SC_AGENT_IMPLEMENTATION(RiverFlowSearchAgent)
    {
        if (!edgeAddr.IsValid())
            return SC_RESULT_ERROR;

        SC_LOG_INFO("RiverFlowSearchAgent begin");
        ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

        ScAddr const& startNodeAddr
            = IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);
        if (!startNodeAddr.IsValid())
        {
            SC_LOG_ERROR("First parameter isn't valid.");
            AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
            return SC_RESULT_ERROR_INVALID_PARAMS;
        }

        ScAddr const& endNodeAddr
            = IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_2);
        if (!endNodeAddr.IsValid())
        {
            SC_LOG_ERROR("Second parameter isn't valid.");
            AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
            return SC_RESULT_ERROR_INVALID_PARAMS;
        }

        ScAddr const& answer = ms_context->CreateNode(ScType::NodeConstStruct);

            auto fromNode = startNodeAddr;
            auto toNode = endNodeAddr;

            auto edge = getEdgeBetween(fromNode, toNode, ScType::EdgeUCommonConst, true);            

            auto statusNode = getStatusNode(edge);
	    auto fromNodeMeta = getIdentifierMeta(fromNode);
	    auto toNodeMeta = getIdentifierMeta(toNode);

            auto edgeToStatusNode = getEdgeBetween(edge, statusNode, ScType::EdgeAccessConstPosPerm, false);
	    auto statusNodeMeta = getIdentifierMeta(statusNode);
	    
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, fromNode);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge);
            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, toNode);

	    for (auto item : fromNodeMeta)
	    {
	      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, item);
	    }

	    for (auto item : toNodeMeta)
	    {
	      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, item);
	    }

            ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, statusNode);
            
	    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edgeToStatusNode);
	    
	    for (auto item : statusNodeMeta)
	    {
	      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, item);
	    }


        AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
        SC_LOG_INFO("RiverFlowSearchAgent end");
        return SC_RESULT_OK;
    }

    std::list<ScAddr> RiverFlowSearchAgent::getIdentifierMeta(const ScAddr& addr)
    {
        auto iterator = ms_context->Iterator5(addr, ScType::EdgeDCommonConst, ScType::LinkConst, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_main_idtf);

        if (iterator->Next())
        {
            return std::list<ScAddr> {
        iterator->Get(1),
        iterator->Get(2),
        iterator->Get(3),
        iterator->Get(4)
            };
        }

        return {};
    }

    ScAddr RiverFlowSearchAgent::getStatusNode(const ScAddr& edge)
    {
        auto iterator = ms_context->Iterator3(ScType::NodeConst, ScType::EdgeAccessConstPosPerm, edge);

        while (iterator->Next())
        {
            auto statusNode = iterator->Get(0);

            if (!ms_context->HelperCheckEdge(Keynodes::concept_parameter, statusNode, ScType::EdgeAccessConstPosPerm))
            {
                continue;
            }

            return statusNode;
        }

        return ScAddr::Empty;
    }

    ScAddr RiverFlowSearchAgent::getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse)
    {
        auto iterator = ms_context->Iterator3(from, type, to);

        if (iterator->Next())
        {
            return iterator->Get(1);
        }

        if (findReverse)
        {
            return getEdgeBetween(to, from, type, false);
        }
    }

}  

