#include "SearchShortestPathAgentModule.hpp"

namespace SearchShortestPathAgentModule
{
SC_IMPLEMENT_MODULE(SearchShortestPathAgentModule)

sc_result SearchShortestPathAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchShortestPathAgentModule");

  SC_AGENT_REGISTER(SearchShortestPathAgent)

  return SC_RESULT_OK;
}

sc_result SearchShortestPathAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchShortestPathAgent)

  return SC_RESULT_OK;
}
} 
