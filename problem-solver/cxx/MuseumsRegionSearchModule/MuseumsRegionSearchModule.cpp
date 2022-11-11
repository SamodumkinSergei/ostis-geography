/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MuseumsRegionSearchModule.hpp"
namespace MuseumsRegionSearchModule
{
SC_IMPLEMENT_MODULE(MuseumsRegionSearchModule)

sc_result MuseumsRegionSearchModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "MuseumsRegionSearchModule");

  SC_AGENT_REGISTER(MuseumsRegionSearch)

  return SC_RESULT_OK;
}

sc_result MuseumsRegionSearchModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(MuseumsRegionSearch)

  return SC_RESULT_OK;
}
}  // namespace MuseumsRegionSearchModule
