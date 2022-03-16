/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
// Меняем везде Example на свое
#include "SearchPostOfficeByTypeModule.hpp"

SC_IMPLEMENT_MODULE(SearchPostOfficeByTypeAgentModule)

sc_result SearchPostOfficeByTypeAgentModule::InitializeImpl()
{
  m_SearchBanksByTypeService.reset(new SearchPostOfficeByTypeAgentPythonService("SearchPostOfficeByTypeAgent/SearchPostOfficeByTypeModule.py")); // тут указывается путь к модулю на python от папки problem-solver/py/services
  m_SearchBanksByTypeService->Run();
  return SC_RESULT_OK;
}

sc_result SearchPostOfficeByTypeAgentModule::ShutdownImpl()
{
  m_SearchBanksByTypeService->Stop();
  m_SearchBanksByTypeService.reset();
  return SC_RESULT_OK;
}
