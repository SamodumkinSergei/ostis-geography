#include "RiversModule.hpp"
namespace RiversModule {
SC_IMPLEMENT_MODULE(RiversModule)

sc_result RiversModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "RiversModule");

  SC_AGENT_REGISTER(TheBiggestBasin)

  return SC_RESULT_OK;
}

sc_result RiversModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(TheBiggestBasin)

  return SC_RESULT_OK;
}
}
