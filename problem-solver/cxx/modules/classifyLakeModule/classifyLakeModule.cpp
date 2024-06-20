/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "classifyLakeModule.hpp"
#include "keynodes/keynodes.hpp"
#include "agents/classifyLakeAgent.hpp"
#include "agents/classifyLakeVAgent.hpp"
#include "agents/classifyLakeDepthAgent.hpp"
using namespace classifyLakeModule;

SC_IMPLEMENT_MODULE(ClassifyLakeModule)

sc_result ClassifyLakeModule::InitializeImpl()
{
  if (!classifyLakeModule::Keynodes::InitGlobal())
    return SC_RESULT_ERROR;

  	SC_AGENT_REGISTER(classifyLakeAgent)
  	SC_AGENT_REGISTER(classifyLakeVAgent)
  	SC_AGENT_REGISTER(classifyLakeDepthAgent)
  return SC_RESULT_OK;
  
}

sc_result ClassifyLakeModule::ShutdownImpl()
{
  	SC_AGENT_UNREGISTER(classifyLakeAgent)
  	SC_AGENT_UNREGISTER(classifyLakeVAgent)
  	SC_AGENT_UNREGISTER(classifyLakeDepthAgent)
  return SC_RESULT_OK;
}
