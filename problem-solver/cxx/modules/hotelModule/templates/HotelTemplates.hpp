/*
 * Author Artsiom Salauyou
 */

#pragma once

#include <sc-memory/sc_addr.hpp>
#include <sc-memory/sc_memory.hpp>

namespace hotelModule
{
class HotelTemplates
{
public:
  static std::string const HOTEL_ALIAS;

  explicit HotelTemplates();

  static std::unique_ptr<ScTemplate> getHotelByMinPricePerNightTemplate(ScAddr const & minPricePerNightAddr);
};
}  
