/*
* Author Teterski Ivan
*/

#include "AutoModule.hpp"
#include "agent/FindSiteAgent.hpp"
#include "keynodes/AutoKeynodes.hpp"


namespace autoModule
{
SC_IMPLEMENT_MODULE(AutoModule)

sc_result AutoModule::InitializeImpl()
{
  if (!AutoKeynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "AutoModule");

  SC_AGENT_REGISTER(FindSiteAgent)

  return SC_RESULT_OK;
}

sc_result AutoModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(FindSiteAgent)

  return SC_RESULT_OK;
}
}