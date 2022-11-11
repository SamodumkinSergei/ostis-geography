/*
 * Author Artsiom Salauyou
 */

#pragma once

#include "sc-memory/kpm/sc_agent.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "searcher/HotelSearcher.hpp"

#include "GetHotelByMinPricePerNightAgent.generated.hpp"

namespace hotelModule {
    class GetHotelByMinPricePerNightAgent : public ScAgent {
        SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
        SC_GENERATED_BODY()

    private:

        std::unique_ptr<HotelSearcher> hotelSearcher;

        bool checkActionClass(ScAddr const &actionAddr);

        static bool isHotel(ScAddr const &hotel);

        static bool isPriceLink(ScAddr const &priceLink);

        static ScAddrVector getPricesLinks(ScAddr const &InputLink);

        void initFields();
    };
}
