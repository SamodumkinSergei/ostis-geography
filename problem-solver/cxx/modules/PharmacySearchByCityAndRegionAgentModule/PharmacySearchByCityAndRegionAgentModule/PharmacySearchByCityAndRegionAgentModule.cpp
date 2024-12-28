#include "PharmacySearchByCityAndRegionAgentModule.hpp"
namespace PharmacySearchByCityAndRegionAgentModule
{
SC_MODULE_REGISTER(PharmacySearchByCityAndRegionAgentModule)
  ->Agent<PharmacySearchByCityAndRegionAgent>();

//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
// void PharmacySearchByCityAndRegionAgentModule::Initialize(ScMemoryContext * context)
// {
//   // if (!Keynodes::InitGlobal())
//   // {
//   //   return SC_RESULT_ERROR;
//   // }

//   // // ScMemoryContext ctx(sc_access_lvl_make_min, "PharmacySearchByCityAndRegionAgentModule");

//   //todo(codegen-removal): Use context->SubscribeAgent<PharmacySearchByCityAndRegionAgent> or UnsubscribeAgent; to register and unregister agent
//  // context->SubscribeAgent<PharmacySearchByCityAndRegionAgent>;

//   // // return SC_RESULT_OK;
// }


// //todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
// void PharmacySearchByCityAndRegionAgentModule::Shutdown(ScMemoryContext * context)
// {
//   //todo(codegen-removal): Use context->SubscribeAgent<PharmacySearchByCityAndRegionAgent> or UnsubscribeAgent; to register and unregister agent
//  // context->UnsubscribeAgent<PharmacySearchByCityAndRegionAgent>;

//   // // return SC_RESULT_OK;
// }
}  // namespace PharmacySearchByCityAndRegionAgentModule
