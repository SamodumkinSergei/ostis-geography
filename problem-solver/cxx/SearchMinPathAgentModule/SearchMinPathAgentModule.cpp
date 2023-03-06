#include "SearchMinPathAgentModule.hpp"

namespace SearchMinPathAgentModule
{
SC_IMPLEMENT_MODULE(SearchMinPathAgentModule)

sc_result SearchMinPathAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchMinPathAgentModule");

  SC_AGENT_REGISTER(SearchMinPathAgent)

  return SC_RESULT_OK;
}

sc_result SearchMinPathAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchMinPathAgent)

  return SC_RESULT_OK;
}
} 
