/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
// Меняем везде Example на свое
#include "ExampleModule.hpp"

SC_IMPLEMENT_MODULE(ExampleModule)

sc_result ExampleModule::InitializeImpl()
{
  m_ExampleService.reset(new ExamplePythonService("ExampleModule/ExampleModule.py")); // тут указывается путь к модулю на python от папки problem-solver/py/services
  m_ExampleService->Run();
  return SC_RESULT_OK;
}

sc_result ExampleModule::ShutdownImpl()
{
  m_ExampleService->Stop();
  m_ExampleService.reset();
  return SC_RESULT_OK;
}
