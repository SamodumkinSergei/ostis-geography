/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "StatusAndDistrictSearchModule.hpp"
namespace StatusAndDistrictSearchModule
{
SC_MODULE_REGISTER(StatusAndDistrictSearchModule)
  ->Agent<StatusAndDistrictSearch>();

//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
/*
{
  if (!Keynodes::InitGlobal())
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "StatusAndDistrictSearchModule");

  //todo(codegen-removal): Use agentContext.SubscribeAgent<StatusAndDistrictSearch> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(StatusAndDistrictSearch)

  return SC_RESULT_OK;
}
*/


//todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
/*
{
  //todo(codegen-removal): Use agentContext.SubscribeAgent<StatusAndDistrictSearch> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(StatusAndDistrictSearch)

  return SC_RESULT_OK;
}
*/
}  // namespace StatusAndDistrictSearchModule
