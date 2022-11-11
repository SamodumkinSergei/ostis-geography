/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "DistanceModule.hpp"

SC_IMPLEMENT_MODULE(DistanceAgentModule)

sc_result DistanceAgentModule::InitializeImpl()
{
  m_DistanceService.reset(new DistanceAgentPythonService("DistanceAgent/DistanceModule.py"));
  m_DistanceService->Run();
  return SC_RESULT_OK;
}

sc_result DistanceAgentModule::ShutdownImpl()
{
  m_DistanceService->Stop();
  m_DistanceService.reset();
  return SC_RESULT_OK;
}
