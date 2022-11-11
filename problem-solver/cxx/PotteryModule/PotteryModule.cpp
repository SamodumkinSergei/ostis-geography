#include "PotteryModule.hpp"
namespace PotteryModule {
SC_IMPLEMENT_MODULE(PotteryModule)

sc_result PotteryModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "PotteryModule");

  SC_AGENT_REGISTER(PotteryDate)

  return SC_RESULT_OK;
}

sc_result PotteryModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(PotteryDate)

  return SC_RESULT_OK;
}
}
