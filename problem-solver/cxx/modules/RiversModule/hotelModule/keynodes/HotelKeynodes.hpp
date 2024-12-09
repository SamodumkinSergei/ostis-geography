/*
 * Author Artsiom Salauyou
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace hotelModule
{
class HotelKeynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const action_get_hotel_by_min_price_per_night{"action_get_hotel_by_min_price_per_night"};

  static inline ScKeynode const nrel_min_price_per_night{"nrel_min_price_per_night"};

  static inline ScKeynode const concept_hotel{"concept_hotel"};

  static inline ScKeynode const concept_map_object{"concept_map_object"};

  static inline ScKeynode const concept_price{"concept_price"};

  static inline ScKeynode const concept_usd{"concept_usd"};

  static inline ScKeynode const concept_hotel_request{"concept_hotel_request"};

};
}  // namespace hotelModule
