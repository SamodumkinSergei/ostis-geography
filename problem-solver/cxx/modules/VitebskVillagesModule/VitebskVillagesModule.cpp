#include "VitebskVillagesModule.hpp"
namespace VitebskVillagesModule
{
SC_MODULE_REGISTER(VitebskVillagesModule)
  ->Agent<LargerVillageByPopulationInTheDistrict>()
  ->Agent<LargerVillageByPopulation>()
  ->Agent<GreatestDistanceToTheRegionalCenter>();

//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
/*
{
  if (!Keynodes::InitGlobal())

  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "VitebskVillagesModule");

  //todo(codegen-removal): Use agentContext.SubscribeAgent<LargerVillageByPopulationInTheDistrict> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(LargerVillageByPopulationInTheDistrict)
  //todo(codegen-removal): Use agentContext.SubscribeAgent<LargerVillageByPopulation> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(LargerVillageByPopulation)
  //todo(codegen-removal): Use agentContext.SubscribeAgent<GreatestDistanceToTheRegionalCenter> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_REGISTER(GreatestDistanceToTheRegionalCenter)

  return SC_RESULT_OK;
}
*/


//todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
/*
{
  //todo(codegen-removal): Use agentContext.SubscribeAgent<LargerVillageByPopulationInTheDistrict> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(LargerVillageByPopulationInTheDistrict)
  //todo(codegen-removal): Use agentContext.SubscribeAgent<LargerVillageByPopulation> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(LargerVillageByPopulation)
  //todo(codegen-removal): Use agentContext.SubscribeAgent<GreatestDistanceToTheRegionalCenter> or UnsubscribeAgent; to register and unregister agent
SC_AGENT_UNREGISTER(GreatestDistanceToTheRegionalCenter)

  return SC_RESULT_OK;
}
*/
}  // namespace VitebskVillagesModule
