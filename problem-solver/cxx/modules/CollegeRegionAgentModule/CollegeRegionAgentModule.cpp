#include "CollegeRegionAgentModule.hpp"

namespace CollegeRegionAgentModule
{
SC_IMPLEMENT_MODULE(CollegeRegionAgentModule)

sc_result CollegeRegionAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "CollegeRegionAgentModule");

  SC_AGENT_REGISTER(CollegeRegionAgent)

  return SC_RESULT_OK;
}

sc_result CollegeRegionAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(CollegeRegionAgent)

  return SC_RESULT_OK;
}
}  