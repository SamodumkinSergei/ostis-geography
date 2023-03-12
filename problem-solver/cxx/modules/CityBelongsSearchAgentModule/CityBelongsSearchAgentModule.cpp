#include "CityBelongsSearchAgentModule.hpp"

namespace CityBelongsSearchAgentModule
{
SC_IMPLEMENT_MODULE(CityBelongsSearchAgentModule)

sc_result CityBelongsSearchAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "CityBelongsSearchAgentModule");

  SC_AGENT_REGISTER(RiverFlowSearchAgent)

  return SC_RESULT_OK;
}

sc_result CityBelongsSearchAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(RiverFlowSearchAgent)

  return SC_RESULT_OK;
}
} 