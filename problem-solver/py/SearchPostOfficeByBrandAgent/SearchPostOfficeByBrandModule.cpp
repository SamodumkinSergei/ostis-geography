/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
// Меняем везде Example на свое
#include "SearchPostOfficeByBrandModule.hpp"

SC_IMPLEMENT_MODULE(SearchPostOfficeByBrandAgentModule)

sc_result SearchPostOfficeByBrandAgentModule::InitializeImpl()
{
  m_SearchPostOfficeByBrandService.reset(new SearchPostOfficeByBrandAgentPythonService("SearchPostOfficeByBrandAgent/SearchPostOfficeByBrandModule.py")); // тут указывается путь к модулю на python от папки problem-solver/py/services
  m_SearchPostOfficeByBrandService->Run();
  return SC_RESULT_OK;
}

sc_result SearchPostOfficeByBrandAgentModule::ShutdownImpl()
{
  m_SearchPostOfficeByBrandService->Stop();
  m_SearchPostOfficeByBrandService.reset();
  return SC_RESULT_OK;
}
