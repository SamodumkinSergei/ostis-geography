/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
// Меняем везде Example на свое
#include "SearchBanksByBrandModule.hpp"

SC_IMPLEMENT_MODULE(SearchBanksByBrandAgentModule)

sc_result SearchBanksByBrandAgentModule::InitializeImpl()
{
  m_SearchBanksByBrandService.reset(new SearchBanksByBrandAgentPythonService("SearchBanksByBrandAgent/SearchBanksByBrandModule.py")); // тут указывается путь к модулю на python от папки problem-solver/py/services
  m_SearchBanksByBrandService->Run();
  return SC_RESULT_OK;
}

sc_result SearchBanksByBrandAgentModule::ShutdownImpl()
{
  m_SearchBanksByBrandService->Stop();
  m_SearchBanksByBrandService.reset();
  return SC_RESULT_OK;
}
