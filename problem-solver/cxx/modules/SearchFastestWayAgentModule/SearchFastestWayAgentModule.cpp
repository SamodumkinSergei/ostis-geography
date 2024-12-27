#include "SearchFastestWayAgentModule.hpp"

namespace SearchFastestWayAgentModule
{
SC_MODULE_REGISTER(SearchFastestWayAgentModule)
  ->Agent<SearchFastestWayAgent>();
void SearchFastestWayAgentModule::Initialize(ScMemoryContext* context){

}
void SearchFastestWayAgentModule::Shutdown(ScMemoryContext* context){
  
}
//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
/*
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchFastestWayAgentModule");

  //todo(codegen-removal): Use agentContext.SubscribeAgent<SearchFastestWayAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(SearchFastestWayAgent)

  return SC_RESULT_OK;
}
*/


//todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
/*
{
  //todo(codegen-removal): Use agentContext.SubscribeAgent<SearchFastestWayAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(SearchFastestWayAgent)

  return SC_RESULT_OK;
}
*/
}  // namespace SearchFastestWayAgentModule
  
