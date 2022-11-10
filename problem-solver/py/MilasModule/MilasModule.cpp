/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
#include "MilasModule.hpp"

SC_IMPLEMENT_MODULE(MilasModule)

sc_result MilasModule::InitializeImpl()
{
  m_MilasService.reset(new MilasPythonService("MilasModule/MilasModule.py"));
  m_MilasService->Run();
  return SC_RESULT_OK;
}

sc_result MilasModule::ShutdownImpl()
{
  m_MilasService->Stop();
  m_MilasService.reset();
  return SC_RESULT_OK;
}