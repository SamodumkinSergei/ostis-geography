#include "SoatoClassificationModule.hpp"

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "agent/SoatoClassificationAgent.hpp"
#include "keynodes/Keynodes.hpp"

namespace soatoClassificationModule
{

SC_IMPLEMENT_MODULE(SoatoClassificationModule)

sc_result SoatoClassificationModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  SC_AGENT_REGISTER(SoatoClassificationAgent);
  return SC_RESULT_OK;
}

sc_result SoatoClassificationModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SoatoClassificationAgent);
  return SC_RESULT_OK;
}

}  // namespace soatoClassificationModule
