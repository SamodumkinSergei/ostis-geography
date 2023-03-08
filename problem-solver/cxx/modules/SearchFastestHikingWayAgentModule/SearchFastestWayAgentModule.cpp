#include "SearchFastestHikingWayAgentModule.hpp"

namespace SearchFastestHikingWayAgentModule
{
SC_IMPLEMENT_MODULE(SearchFastestHikingWayAgentModule)

sc_result SearchFastestHikingWayAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchFastestHikingWayAgentModule");

  SC_AGENT_REGISTER(SearchFastestHikingWayAgent)

  return SC_RESULT_OK;
}

sc_result SearchFastestHikingWayAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchFastestHikingWayAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchFastestHikingWayAgentModule
  