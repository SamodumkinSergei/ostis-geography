/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
#include "PharmaciesModule.hpp"

SC_IMPLEMENT_MODULE(PharmaciesModule)

sc_result PharmaciesModule::InitializeImpl()
{
  m_PharmaciesService.reset(new PharmaciesPythonService("pharmaciesModule/PharmaciesModule.py"));
  m_PharmaciesService->Run();
  return SC_RESULT_OK;
}

sc_result PharmaciesModule::ShutdownImpl()
{
  m_PharmaciesService->Stop();
  m_PharmaciesService.reset();
  return SC_RESULT_OK;
}
