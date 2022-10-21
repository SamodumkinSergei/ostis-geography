/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "HotelsModule.hpp"

SC_IMPLEMENT_MODULE(HotelsModule)

sc_result HotelsModule::InitializeImpl()
{
  m_HotelsService.reset(new HotelsPythonService("HotelsModule/HotelsModule.py"));
  m_HotelsService->Run();
  return SC_RESULT_OK;
}

sc_result HotelsModule::ShutdownImpl()
{
  m_HotelsService->Stop();
  m_HotelsService.reset();
  return SC_RESULT_OK;
}
