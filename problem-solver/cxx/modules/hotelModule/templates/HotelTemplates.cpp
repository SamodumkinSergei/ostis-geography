/*
 * Author Artsiom Salauyou
 */

#include "keynodes/HotelKeynodes.hpp"

#include "HotelTemplates.hpp"

namespace hotelModule
{
std::string const HotelTemplates::HOTEL_ALIAS = "_hotel";

HotelTemplates::HotelTemplates() = default;

std::unique_ptr<ScTemplate> HotelTemplates::getHotelByMinPricePerNightTemplate(ScAddr const & minPricePerNightAddr)
{
  std::unique_ptr<ScTemplate> hotelByMinPricePerNightTemplate = std::make_unique<ScTemplate>();

  hotelByMinPricePerNightTemplate->Quintuple(
      ScType::VarNode >> HOTEL_ALIAS,
      ScType::VarCommonArc,
      minPricePerNightAddr,
      ScType::VarPermPosArc,
      HotelKeynodes::nrel_min_price_per_night);
  return hotelByMinPricePerNightTemplate;
}
}  
