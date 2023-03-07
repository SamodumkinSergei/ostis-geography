#include "SearchPathAgentModule.hpp"

namespace SearchPathAgentModule
{
SC_IMPLEMENT_MODULE(SearchPathAgentModule)

sc_result SearchPathAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchPathAgentModule");

  SC_AGENT_REGISTER(SearchPathAgentModule)

  return SC_RESULT_OK;
}

sc_result SearchPathAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchPathAgentModule)

  return SC_RESULT_OK;
}
}  // namespace SearchPathAgentModule
  