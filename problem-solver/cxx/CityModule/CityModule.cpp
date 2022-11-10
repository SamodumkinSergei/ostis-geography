/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
// Меняем везде Example на свое
#include "CityModule.hpp"

SC_IMPLEMENT_MODULE(CityModule)

sc_result CityModule::InitializeImpl()
{
  m_CityService.reset(new CityPythonService("CityModule/CityModule.py")); // тут указывается путь к модулю на python от папки problem-solver/py/services
  m_CityService->Run();
  return SC_RESULT_OK;
}

sc_result CityModule::ShutdownImpl()
{
  m_CityService->Stop();
  m_CityService.reset();
  return SC_RESULT_OK;
}