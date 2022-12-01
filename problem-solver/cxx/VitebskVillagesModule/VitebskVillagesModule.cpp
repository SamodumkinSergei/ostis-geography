#include "VitebskVillagesModule.hpp"
namespace VitebskVillagesModule {
SC_IMPLEMENT_MODULE(VitebskVillagesModule)

sc_result VitebskVillagesModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "VitebskVillagesModule");

  SC_AGENT_REGISTER(LargerVillageByPopulation)

  return SC_RESULT_OK;
}

sc_result VitebskVillagesModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(LargerVillageByPopulation)

  return SC_RESULT_OK;
}
}
