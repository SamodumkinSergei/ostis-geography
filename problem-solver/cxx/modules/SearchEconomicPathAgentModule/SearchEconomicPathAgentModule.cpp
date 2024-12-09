#include "SearchEconomicPathAgentModule.hpp"

namespace SearchEconomicPathAgentModule
{
SC_MODULE_REGISTER(SearchEconomicPathAgentModule)
  ->Agent<SearchEconomicPathAgent>();

//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
/*
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchEconomicPathAgentModule");

  //todo(codegen-removal): Use agentContext.SubscribeAgent<SearchEconomicPathAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(SearchEconomicPathAgent)

  return SC_RESULT_OK;
}
*/


//todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
/*
{
  //todo(codegen-removal): Use agentContext.SubscribeAgent<SearchEconomicPathAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(SearchEconomicPathAgent)

  return SC_RESULT_OK;
}
*/
}  // namespace SearchEconomicPathAgentModule
