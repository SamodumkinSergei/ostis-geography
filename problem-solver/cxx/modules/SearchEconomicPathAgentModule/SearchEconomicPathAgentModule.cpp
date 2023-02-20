#include "SearchEconomicPathAgentModule.hpp"

namespace SearchEconomicPathAgentModule
{
SC_IMPLEMENT_MODULE(SearchEconomicPathAgentModule)

sc_result SearchEconomicPathAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchEconomicPathAgentModule");

  SC_AGENT_REGISTER(SearchEconomicPathAgent)

  return SC_RESULT_OK;
}

sc_result SearchEconomicPathAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchEconomicPathAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchEconomicPathAgentModule
