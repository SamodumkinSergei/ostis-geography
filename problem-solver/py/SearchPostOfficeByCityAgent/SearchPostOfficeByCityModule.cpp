/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
// Меняем везде Example на свое
#include "SearchPostOfficeByCityModule.hpp"

SC_IMPLEMENT_MODULE(SearchPostOfficeByCityAgentModule)

sc_result SearchPostOfficeByCityAgentModule::InitializeImpl()
{
  m_SearchPostOfficeByCityService.reset(new SearchPostOfficeByCityAgentPythonService("SearchPostOfficeByCityAgent/SearchPostOfficeByCityModule.py")); // тут указывается путь к модулю на python от папки problem-solver/py/services
  m_SearchPostOfficeByCityService->Run();
  return SC_RESULT_OK;
}

sc_result SearchPostOfficeByCityAgentModule::ShutdownImpl()
{
  m_SearchPostOfficeByCityService->Stop();
  m_SearchPostOfficeByCityService.reset();
  return SC_RESULT_OK;
}
