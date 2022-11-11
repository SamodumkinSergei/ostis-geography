/*
 * Author Artsiom Salauyou
 */

#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "HotelKeynodes.generated.hpp"

namespace hotelModule {
    class HotelKeynodes : public ScObject {
        SC_CLASS()
        SC_GENERATED_BODY()

    public:
        SC_PROPERTY(Keynode("action_get_hotel_by_min_price_per_night"), ForceCreate)
        static ScAddr action_get_hotel_by_min_price_per_night;

        SC_PROPERTY(Keynode("nrel_min_price_per_night"), ForceCreate)
        static ScAddr nrel_min_price_per_night;

        SC_PROPERTY(Keynode("concept_hotel"), ForceCreate)
        static ScAddr concept_hotel;

        SC_PROPERTY(Keynode("concept_map_object"), ForceCreate)
        static ScAddr concept_map_object;

        SC_PROPERTY(Keynode("concept_price"), ForceCreate)
        static ScAddr concept_price;

        SC_PROPERTY(Keynode("concept_usd"), ForceCreate)
        static ScAddr concept_usd;
    };
}
