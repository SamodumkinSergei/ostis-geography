/*
 * Author Artsiom Salauyou
 */

#include "keynodes/HotelKeynodes.hpp"

#include "agent/GetHotelByMinPricePerNightAgent.hpp"

#include "HotelModule.hpp"

using namespace hotelModule;

// Регистрация агентов
SC_MODULE_REGISTER(HotelModule)
  ->Agent<GetHotelByMinPricePerNightAgent>();























