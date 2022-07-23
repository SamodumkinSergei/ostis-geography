/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
#include "LakesModule.hpp"

SC_IMPLEMENT_MODULE(LakesModule)

sc_result LakesModule::InitializeImpl()
{
  m_LakesService.reset(new LakesPythonService("LakesModule/LakesModule.py"));
  m_LakesService->Run();
  return SC_RESULT_OK;
}

sc_result LakesModule::ShutdownImpl()
{
  m_LakesService->Stop();
  m_LakesService.reset();
  return SC_RESULT_OK;
}
