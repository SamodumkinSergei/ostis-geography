#include "AdminModule.hpp"

SC_MODULE_REGISTER(AdminModule)
  ->Agent<adminModule::GetAdminBuildingRegion>()
  ->Agent<adminModule::GetAdminBuildingDistrict>();

//todo(codegen-removal): if needed  ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
// void AdminModule::Initialize(ScMemoryContext * context) 
// {
//   // if (!AdminModule::AdminKeynodes::InitGlobal())  // AdminModule это название пространства в котором находятся агенты и
//   //                                                 // другие классы которые используются для работы агентов
//   // {
//   //   return SC_RESULT_ERROR;
//   // }

//   // тут AdminModule может быть любой строкой, но для простоты исползуется название пространства
//   //todo(codegen-removal): Use context.SubscribeAgent<adminModule::GetAdminBuildingRegion> or UnsubscribeAgent; to register and unregister agent
//  // context->SubscribeAgent<adminModule::GetAdminBuildingRegion>();
//   //todo(codegen-removal): Use context.SubscribeAgent<adminModule::GetAdminBuildingDistrict> or UnsubscribeAgent; to register and unregister agent
//  // context->SubscribeAgent<AdminModule::GetAdminBuildingDistrict>();
//   // регистрируем свои агенты, можно сколько угодно агентов зарегистрировать, если этого не сдлеать агент работать не
//   // будет, так как не загружен в память.

//   // return SC_RESULT_OK;
// }


// //todo(codegen-removal): if needed  ScModule::Shutdown and move all non-agents code from previous shutdown method
// void AdminModule::Shutdown(ScMemoryContext * context)
// {
//   //todo(codegen-removal): Use context.SubscribeAgent<adminModule::GetAdminBuildingRegion> or UnsubscribeAgent; to register and unregister agent
//   // context->UnsubscribeAgent<adminModule::GetAdminBuildingRegion>();
//   //todo(codegen-removal): Use context.SubscribeAgent<adminModule::GetAdminBuildingDistrict> or UnsubscribeAgent; to register and unregister agent
//   // context->UnsubscribeAgent<adminModule::GetAdminBuildingDistrict>();
//   // по аналогии с регистрацией агентов в памяти, убираем их из памяти, прописать для каждого агента в модуле

//   // return SC_RESULT_OK;
// }

