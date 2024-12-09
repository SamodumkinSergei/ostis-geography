#include "RiversModule.hpp"
namespace RiversModule
{
// SC_IMPLEMENT_MODULE(RiversModule)
SC_MODULE_REGISTER(RiversModule)
  ->Agent<TheBiggestBasinInRegion>()
  ->Agent<LongerRiver>()
  ->Agent<LongestInRegion>()
  ->Agent<BiggerBasin>()
  ->Agent<ShorterRiver>();


// void RiversModule::Initialize(ScMemoryContext * context)
// {
//   // if (!Keynodes::InitGlobal())
//   // {
//   //   return SC_RESULT_ERROR;
//   // }

//   // ScMemoryContext ctx(sc_access_lvl_make_min, "RiversModule");

//  // context->SubscribeAgent<TheBiggestBasinInRegion>;
//  // context->SubscribeAgent<LongerRiver>;
//  // context->SubscribeAgent<LongestInRegion>;
//  // context->SubscribeAgent<BiggerBasin>;
//  // context->SubscribeAgent<ShorterRiver>;

//   // return SC_RESULT_OK;
// }

// void RiversModule::Shutdown(ScMemoryContext * context)
// {
//  // context->UnsubscribeAgent<TheBiggestBasinInRegion>;
//  // context->UnsubscribeAgent<LongerRiver>;
//  // context->UnsubscribeAgent<LongestInRegion>;
//  // context->UnsubscribeAgent<BiggerBasin>;
//  // context->UnsubscribeAgent<ShorterRiver>;
//   // return SC_RESULT_OK;
// }
}  // namespace RiversModule
