/*
 * Author Artsiom Salauyou
 */

#pragma once

#include <sc-memory/sc_addr.hpp>
#include <sc-memory/sc_memory.hpp>

#include "templates/HotelTemplates.hpp"

namespace hotelModule {
    class HotelSearcher {
    private:
        ScMemoryContext * context;

        std::unique_ptr<HotelTemplates> hotelTemplates;
    public:
        explicit HotelSearcher(ScMemoryContext *ms_context);

        ScAddr searchHotelByMinPricePerNight(ScAddr const & minPricePerNightAddr);
    };
}
