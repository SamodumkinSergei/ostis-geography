#include "FindingTimeToGetToMinskAgentModule.hpp"

namespace FindingTimeToGetToMinskAgentModule
{
SC_IMPLEMENT_MODULE(FindingTimeToGetToMinskAgentModule)

sc_result FindingTimeToGetToMinskAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "FindingTimeToGetToMinskAgentModule");

  SC_AGENT_REGISTER(FindingTimeToGetToMinskAgent)

  return SC_RESULT_OK;
}

sc_result FindingTimeToGetToMinskAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(FindingTimeToGetToMinskAgent)

  return SC_RESULT_OK;
}
}  // namespace FindingTimeToGetToMinskAgentModule
