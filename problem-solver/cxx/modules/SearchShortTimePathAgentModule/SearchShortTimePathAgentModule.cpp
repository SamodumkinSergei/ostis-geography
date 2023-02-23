#include "SearchShortTimePathAgentModule.hpp"

namespace SearchShortTimePathAgentModule
{
SC_IMPLEMENT_MODULE(SearchShortTimePathAgentModule)

sc_result SearchShortTimePathAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchShortTimePathAgentModule");

  SC_AGENT_REGISTER(SearchShortTimePathAgent)

  return SC_RESULT_OK;
}

sc_result SearchShortTimePathAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchShortTimePathAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchShortTimePathAgentModule
