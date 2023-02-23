#include "SearchCostToBaranovichiAgentModule.hpp"

namespace SearchCostToBaranovichiAgentModule
{
SC_IMPLEMENT_MODULE(SearchCostToBaranovichiAgentModule)

sc_result SearchCostToBaranovichiAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchCostToBaranovichiAgentModule");

  SC_AGENT_REGISTER(SearchCostToBaranovichiAgent)

  return SC_RESULT_OK;
}

sc_result SearchCostToBaranovichiAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchCostToBaranovichiAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchCostToBaranovichiAgentModule
