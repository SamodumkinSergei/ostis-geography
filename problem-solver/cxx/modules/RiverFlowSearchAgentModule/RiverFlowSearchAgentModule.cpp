#include "RiverFlowSearchAgentModule.hpp"

namespace RiverFlowSearchAgentModule
{
SC_IMPLEMENT_MODULE(RiverFlowSearchAgentModule)

sc_result RiverFlowSearchAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "RiverFlowSearchAgentModule");

  SC_AGENT_REGISTER(RiverFlowSearchAgent)

  return SC_RESULT_OK;
}

sc_result RiverFlowSearchAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(RiverFlowSearchAgent)

  return SC_RESULT_OK;
}
}  