/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "StreetTranslatorModule.hpp"

SC_IMPLEMENT_MODULE(StreetTranslatorModule)

sc_result StreetTranslatorModule::InitializeImpl()
{
  m_StreetTranslatorService.reset(new StreetTranslatorPythonService("StreetTranslatorModule/StreetTranslatorModule.py"));
  m_StreetTranslatorService->Run();
  return SC_RESULT_OK;
}

sc_result StreetTranslatorModule::ShutdownImpl()
{
  m_StreetTranslatorService->Stop();
  m_StreetTranslatorService.reset();
  return SC_RESULT_OK;
}
