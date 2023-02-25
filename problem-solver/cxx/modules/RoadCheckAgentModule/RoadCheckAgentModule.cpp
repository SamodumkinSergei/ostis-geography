#include "RoadCheckAgentModule.hpp"

namespace RoadCheckAgentModule
{
SC_IMPLEMENT_MODULE(RoadCheckAgentModule)

sc_result RoadCheckAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "RoadCheckAgentModule");

  SC_AGENT_REGISTER(RoadCheckAgent)

  return SC_RESULT_OK;
}

sc_result RoadCheckAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(RoadCheckAgent)

  return SC_RESULT_OK;
}
}  