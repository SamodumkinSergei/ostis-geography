#include "VillagesModule.hpp"
#include "agents/VillageSearchAgent.hpp"

namespace VillagesModule
{
SC_IMPLEMENT_MODULE(VillagesModule)

sc_result VillagesModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "VillagesModule");

  SC_AGENT_REGISTER(VillageSearchAgent)

  return SC_RESULT_OK;
}

sc_result VillagesModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(VillageSearchAgent)

  return SC_RESULT_OK;
}
}  // namespace VillagesModule