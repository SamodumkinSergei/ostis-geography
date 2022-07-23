/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
// Меняем везде Example на свое
#include "SearchBanksByCityModule.hpp"

SC_IMPLEMENT_MODULE(SearchBanksByCityAgentModule)

sc_result SearchBanksByCityAgentModule::InitializeImpl()
{
  m_SearchBanksByCityService.reset(new SearchBanksByCityAgentPythonService("SearchBanksByCityAgent/SearchBanksByCityModule.py")); // тут указывается путь к модулю на python от папки problem-solver/py/services
  m_SearchBanksByCityService->Run();
  return SC_RESULT_OK;
}

sc_result SearchBanksByCityAgentModule::ShutdownImpl()
{
  m_SearchBanksByCityService->Stop();
  m_SearchBanksByCityService.reset();
  return SC_RESULT_OK;
}
