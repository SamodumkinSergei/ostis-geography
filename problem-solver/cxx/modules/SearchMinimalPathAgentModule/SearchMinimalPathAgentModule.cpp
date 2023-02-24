#include "SearchMinimalPathAgentModule.hpp"

namespace SearchMinimalPathAgentModule
{
SC_IMPLEMENT_MODULE(SearchMinimalPathAgentModule)

sc_result SearchMinimalPathAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchMinimalPathAgentModule");

  SC_AGENT_REGISTER(SearchMinimalPathAgent)

  return SC_RESULT_OK;
}

sc_result SearchMinimalPathAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchMinimalPathAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchMinimalPathAgentModule
