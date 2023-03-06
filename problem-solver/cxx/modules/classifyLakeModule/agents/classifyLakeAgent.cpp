/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>
#include <sc-agents-common/keynodes/coreKeynodes.hpp>
#include "classifyLakeAgent.hpp"
#include "sc-core/sc_helper.h"
#include <sc-memory/sc_link.hpp>
#include <sc-memory/sc_wait.hpp>
#include <sc-memory/sc_stream.hpp>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using namespace utils;

namespace classifyLakeModule
{

	 SC_AGENT_IMPLEMENTATION(classifyLakeAgent)
		{
		    if (!edgeAddr.IsValid())
	    return SC_RESULT_ERROR;

	  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
	  ScAddr param = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
	  if (!param.IsValid())
	    return SC_RESULT_ERROR_INVALID_PARAMS;

	  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
	  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, param);

	  ScIterator5Ptr iterator5 = IteratorUtils::getIterator5(ms_context.get(), param, Keynodes::nrel_area, true);
	  if(iterator5->Next())
	  {
	  	ScAddr url = iterator5->Get(2);//получаем адрес узла с площадью
        ScLink lnk(*ms_context, url);
        system("echo 1");
        float const val = lnk.Get<float>();
        system("echo 2");
        if (val >= 100)
        {
        	system("echo 3");
        	ScAddr edge1 = ms_context->CreateEdge(ScType::EdgeDCommonConst, param, Keynodes::large);
        	ScAddr edge2 = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_area_classification, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge2);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::large);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_area_classification);
        }
        else
        {
        system("echo 4");
        	ScAddr edge1 = ms_context->CreateEdge(ScType::EdgeDCommonConst, param, Keynodes::shallow);
        	ScAddr edge2 = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_area_classification, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge2);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::shallow);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_area_classification);
        }
	  }
	  system("echo 5");
	  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
	  return SC_RESULT_OK;
        }
}
