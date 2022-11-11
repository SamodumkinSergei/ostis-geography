/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "VillagesPopulationModule.hpp"

SC_IMPLEMENT_MODULE(VillagesPopulationAgentModule)

sc_result VillagesPopulationAgentModule::InitializeImpl()
{
  m_VillagesPopulationService.reset(new VillagesPopulationAgentPythonService("VillagesPopulationAgent/VillagesPopulationModule.py"));
  m_VillagesPopulationService->Run();
  return SC_RESULT_OK;
}

sc_result VillagesPopulationAgentModule::ShutdownImpl()
{
  m_VillagesPopulationService->Stop();
  m_VillagesPopulationService.reset();
  return SC_RESULT_OK;
}
