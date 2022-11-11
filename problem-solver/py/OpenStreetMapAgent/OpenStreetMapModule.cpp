/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "OpenStreetMapModule.hpp"

SC_IMPLEMENT_MODULE(OpenStreetMapAgentModule)

sc_result OpenStreetMapAgentModule::InitializeImpl()
{
  m_OpenStreetMapService.reset(new OpenStreetMapAgentPythonService("OpenStreetMapAgent/OpenStreetMapModule.py"));
  m_OpenStreetMapService->Run();
  return SC_RESULT_OK;
}

sc_result OpenStreetMapAgentModule::ShutdownImpl()
{
  m_OpenStreetMapService->Stop();
  m_OpenStreetMapService.reset();
  return SC_RESULT_OK;
}
