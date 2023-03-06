#include "SearchFastestWayToBerestovitsaBorderCrossingAgentModule.hpp"

namespace SearchFastestWayToBerestovitsaBorderCrossingAgentModule
{
SC_IMPLEMENT_MODULE(SearchFastestWayToBerestovitsaBorderCrossingAgentModule)

sc_result SearchFastestWayToBerestovitsaBorderCrossingAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchFastestWayToBerestovitsaBorderCrossingAgentModule");

  SC_AGENT_REGISTER(SearchFastestWayToBerestovitsaBorderCrossingAgent)

  return SC_RESULT_OK;
}

sc_result SearchFastestWayToBerestovitsaBorderCrossingAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchFastestWayToBerestovitsaBorderCrossingAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchFastestWayToBerestovitsaBorderCrossingAgentModule