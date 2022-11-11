/*
 * Author Artsiom Salauyou
 */

#include "keynodes/HotelKeynodes.hpp"

#include "agent/GetHotelByMinPricePerNightAgent.hpp"

#include "HotelModule.hpp"

using namespace hotelModule;

SC_IMPLEMENT_MODULE(HotelModule)

sc_result HotelModule::InitializeImpl() {
    if (hotelModule::HotelKeynodes::InitGlobal() == SC_FALSE)
        return SC_RESULT_ERROR;

    SC_AGENT_REGISTER(GetHotelByMinPricePerNightAgent)

    return SC_RESULT_OK;
}

sc_result HotelModule::ShutdownImpl() {
    SC_AGENT_UNREGISTER(GetHotelByMinPricePerNightAgent)

    return SC_RESULT_OK;
}
