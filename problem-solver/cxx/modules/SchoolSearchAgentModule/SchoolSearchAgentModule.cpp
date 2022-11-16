#include "SchoolSearchAgentModule.hpp"
namespace SchoolSearchAgentModule
{
SC_IMPLEMENT_MODULE(SchoolSearchAgentModule)

sc_result SchoolSearchAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SchoolSearchAgentModule");

  SC_AGENT_REGISTER(SchoolSearchAgent)

  return SC_RESULT_OK;
}

sc_result SchoolSearchAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SchoolSearchAgent)

  return SC_RESULT_OK;
}
}  // namespace SchoolSearchAgentModule
