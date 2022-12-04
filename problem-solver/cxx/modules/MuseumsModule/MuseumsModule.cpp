/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MuseumsModule.hpp"
namespace MuseumsModule
{
SC_IMPLEMENT_MODULE(MuseumsModule)

sc_result MuseumsModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "MuseumsModule");

  SC_AGENT_REGISTER(SearchMuseumsByRegion)

  return SC_RESULT_OK;
}

sc_result MuseumsModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SearchMuseumsByRegion)

  return SC_RESULT_OK;
}
}  // namespace MuseumsModule
