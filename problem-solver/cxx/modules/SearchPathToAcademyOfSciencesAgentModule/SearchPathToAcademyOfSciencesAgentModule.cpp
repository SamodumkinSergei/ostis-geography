#include "SearchPathToAcademyOfSciencesAgentModule.hpp"

namespace SearchPathToAcademyOfSciencesAgentModule
{
SC_IMPLEMENT_MODULE(SearchPathToAcademyOfSciencesAgentModule)

sc_result SearchPathToAcademyOfSciencesAgentModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "SearchPathToAcademyOfSciencesAgentModule");

  SC_AGENT_REGISTER(SearchPathToAcademyOfSciencesAgent)

  return SC_RESULT_OK;
}

sc_result SearchPathToAcademyOfSciencesAgentModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchPathToAcademyOfSciencesAgent)

  return SC_RESULT_OK;
}
}  // namespace SearchShortTimePathAgentModule
