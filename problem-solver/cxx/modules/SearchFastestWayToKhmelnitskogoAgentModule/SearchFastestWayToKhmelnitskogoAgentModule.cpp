#include "SearchFastestWayToKhmelnitskogoAgentModule.hpp"

namespace SearchFastestWayToKhmelnitskogoAgentModule
{
SC_IMPLEMENT_MODULE(SearchFastestWayToKhmelnitskogoAgentModule)

sc_result SearchFastestWayToKhmelnitskogoAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchFastestWayToKhmelnitskogoAgentModule");

  SC_AGENT_REGISTER(SearchFastestWayToKhmelnitskogoAgent)

  return SC_RESULT_OK;
}

sc_result SearchFastestWayToKhmelnitskogoAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchFastestWayToKhmelnitskogoAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchFastestWayToKhmelnitskogoAgentModule