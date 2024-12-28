#include "SchoolSearchAgentModule.hpp"
namespace SchoolSearchAgentModule
{
// SC_IMPLEMENT_MODULE(SchoolSearchAgentModule)
SC_MODULE_REGISTER(SchoolSearchAgentModule)
  ->Agent<SchoolSearchAgent>();

// void SchoolSearchAgentModule::Initialize(ScMemoryContext * context)
// {
//   // if (!ScKeynodes::InitGlobal())
//   // {
//   //   return SC_RESULT_ERROR;
//   // }

//   // ScMemoryContext ctx(sc_access_lvl_make_min, "SchoolSearchAgentModule");

//  // context->SubscribeAgent<SchoolSearchAgent>;

//   // return SC_RESULT_OK;
// }

// void SchoolSearchAgentModule::Shutdown(ScMemoryContext * context)
// {
//  // context->UnsubscribeAgent<SchoolSearchAgent>;

//   // return SC_RESULT_OK;
// }
}  // namespace SchoolSearchAgentModule
