/*
 * Author Artsiom Salauyou
 */

#include "keynodes/HotelKeynodes.hpp"

#include "agent/GetHotelByMinPricePerNightAgent.hpp"

#include "HotelModule.hpp"

using namespace hotelModule;

SC_MODULE_REGISTER(HotelModule)
  ->Agent<GetHotelByMinPricePerNightAgent>();

// //todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
// void HotelModule::Initialize(ScMemoryContext * context)
// {
//   // if (hotelModule::HotelKeynodes::InitGlobal() == SC_FALSE)
//   //   return SC_RESULT_ERROR;

//   //todo(codegen-removal): Use context->SubscribeAgent<GetHotelByMinPricePerNightAgent> or UnsubscribeAgent; to register and unregister agent
//  // context->SubscribeAgent<GetHotelByMinPricePerNightAgent>;


//   // return SC_RESULT_OK;
// }

// void Shutdown(ScMemoryContext * context)
// //todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
// {
//   //todo(codegen-removal): Use context->SubscribeAgent<GetHotelByMinPricePerNightAgent> or UnsubscribeAgent; to register and unregister agent
//  // context->UnsubscribeAgent<GetHotelByMinPricePerNightAgent>;

//   // return SC_RESULT_OK;
// }

