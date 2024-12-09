#include "SoatoClassificationModule.hpp"

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "agent/SoatoClassificationAgent.hpp"
#include "keynodes/Keynodes.hpp"

namespace soatoClassificationModule
{

SC_MODULE_REGISTER(SoatoClassificationModule)
  ->Agent<SoatoClassificationAgent>();

//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
/*
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  //todo(codegen-removal): Use agentContext.SubscribeAgent<SoatoClassificationAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(SoatoClassificationAgent);
  return SC_RESULT_OK;
}
*/


//todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
/*
{
  //todo(codegen-removal): Use agentContext.SubscribeAgent<SoatoClassificationAgent> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(SoatoClassificationAgent);
  return SC_RESULT_OK;
}
*/
}  // namespace soatoClassificationModule
