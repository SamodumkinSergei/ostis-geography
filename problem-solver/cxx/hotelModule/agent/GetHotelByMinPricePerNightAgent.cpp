/*
 * Author Artsiom Salauyou
 */

#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/HotelKeynodes.hpp"

#include "GetHotelByMinPricePerNightAgent.hpp"

using namespace hotelModule;

SC_AGENT_IMPLEMENTATION(GetHotelByMinPricePerNightAgent) {
    ScAddr actionAddr = otherAddr;

    if (checkActionClass(actionAddr) == SC_FALSE)
        return SC_RESULT_OK;

    SC_LOG_DEBUG("GetHotelByMinPricePerNightAgent started");

    ScAddr inputPriceLink =
            utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_1);

    ScAddrVector minPricesPerNight = getPricesLinks(inputPriceLink);

    ScAddrVector answerVector;
    initFields();

    try {
        ScAddr hotel;
        if (!minPricesPerNight.empty()) {
            for (ScAddr minPricePerNight: minPricesPerNight) {
                hotel = hotelSearcher->searchHotelByMinPricePerNight(minPricePerNight);
                if (isHotel(hotel))
                    answerVector.push_back(hotel);
            }
        } else
            SC_LOG_WARNING("No hotels found");
    }
    catch (utils::ScException &) {
        utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerVector, false);
        SC_LOG_DEBUG("GetHotelByMinPricePerNightAgent finished");
        return SC_RESULT_ERROR;
    }

    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerVector, true);
    SC_LOG_DEBUG("GetHotelByMinPricePerNightAgent finished");
    return SC_RESULT_OK;
}

void GetHotelByMinPricePerNightAgent::initFields() {
    this->hotelSearcher = std::make_unique<HotelSearcher>(&m_memoryCtx);
}

bool GetHotelByMinPricePerNightAgent::checkActionClass(const ScAddr &actionNode) {
    return m_memoryCtx.HelperCheckEdge(
            HotelKeynodes::action_get_hotel_by_min_price_per_night, actionNode, ScType::EdgeAccessConstPosPerm);
}

ScAddrVector GetHotelByMinPricePerNightAgent::getPricesLinks(const ScAddr &inputLink) {
    auto minPriceLinkContent = ms_context->GetLinkContent(inputLink);
    ScAddrVector links = ms_context->FindLinksByContent(minPriceLinkContent);

    ScAddrVector resultVector;
    for (ScAddr link: links) {
        if (isPriceLink(link) && link != inputLink)
            resultVector.push_back(link);
    }
    return resultVector;
}

bool GetHotelByMinPricePerNightAgent::isHotel(const ScAddr &hotel) {
    return ms_context->HelperCheckEdge(HotelKeynodes::concept_hotel, hotel, ScType::EdgeAccessConstPosPerm) &&
           ms_context->HelperCheckEdge(HotelKeynodes::concept_map_object, hotel, ScType::EdgeAccessConstPosPerm);
}

bool GetHotelByMinPricePerNightAgent::isPriceLink(const ScAddr &priceLink) {
    return ms_context->HelperCheckEdge(HotelKeynodes::concept_price, priceLink, ScType::EdgeAccessConstPosPerm) &&
           ms_context->HelperCheckEdge(HotelKeynodes::concept_usd, priceLink, ScType::EdgeAccessConstPosPerm);
}
