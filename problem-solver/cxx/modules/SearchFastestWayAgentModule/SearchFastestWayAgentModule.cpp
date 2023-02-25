#include "SearchFastestWayAgentModule.hpp"

namespace SearchFastestWayAgentModule
{
SC_IMPLEMENT_MODULE(SearchFastestWayAgentModule)

sc_result SearchFastestWayAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchFastestWayAgentModule");

  SC_AGENT_REGISTER(SearchFastestWayAgent)

  return SC_RESULT_OK;
}

sc_result SearchFastestWayAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchFastestWayAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchFastestWayAgentModule
  