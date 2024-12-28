#include "PotteryModule.hpp"
namespace PotteryModule
{
// SC_IMPLEMENT_MODULE(PotteryModule)
SC_MODULE_REGISTER(PotteryModule)
  ->Agent<PotteryDate>();

// void PotteryModule::Initialize(ScMemoryContext * context)
// {
//   // if (!Keynodes::InitGlobal())
//   // {
//   //   return SC_RESULT_ERROR;
//   // }

//   // ScMemoryContext ctx(sc_access_lvl_make_min, "PotteryModule");

//  // context->SubscribeAgent<PotteryDate>;

//   // // return SC_RESULT_OK;
// }

// void PotteryModule::Shutdown(ScMemoryContext * context)
// {
//  // context->UnsubscribeAgent<PotteryDate>;

//   // // return SC_RESULT_OK;
// }
}  // namespace PotteryModule
