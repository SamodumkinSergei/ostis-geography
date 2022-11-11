/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "PopulationComparisonModule.hpp"

SC_IMPLEMENT_MODULE(PopulationComparisonAgentModule)

sc_result PopulationComparisonAgentModule::InitializeImpl()
{
  m_PopulationComparisonService.reset(new PopulationComparisonAgentPythonService("PopulationComparisonAgent/PopulationComparisonModule.py"));
  m_PopulationComparisonService->Run();
  return SC_RESULT_OK;
}

sc_result PopulationComparisonAgentModule::ShutdownImpl()
{
  m_PopulationComparisonService->Stop();
  m_PopulationComparisonService.reset();
  return SC_RESULT_OK;
}
