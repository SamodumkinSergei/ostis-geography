#include "VillagesModule.hpp"
#include "agents/VillageSearchAgent.hpp"

namespace VillagesModule
{
SC_MODULE_REGISTER(VillagesModule)
  ->Agent<VillageSearchAgent>();

//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
/*
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "VillagesModule");

  //todo(codegen-removal): Use agentContext.SubscribeAgent<VillageSearchAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(VillageSearchAgent)

  return SC_RESULT_OK;
}
*/


//todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
/*
{
  //todo(codegen-removal): Use agentContext.SubscribeAgent<VillageSearchAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(VillageSearchAgent)

  return SC_RESULT_OK;
}
*/
}  // namespace VillagesModule
