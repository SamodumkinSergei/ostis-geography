/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "StatusAndDistrictSearchModule.hpp"
namespace StatusAndDistrictSearchModule
{
SC_IMPLEMENT_MODULE(StatusAndDistrictSearchModule)

sc_result StatusAndDistrictSearchModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "StatusAndDistrictSearchModule");

  SC_AGENT_REGISTER(StatusAndDistrictSearch)

  return SC_RESULT_OK;
}

sc_result StatusAndDistrictSearchModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(StatusAndDistrictSearch)

  return SC_RESULT_OK;
}
}  // namespace StatusAndDistrictSearchModule
