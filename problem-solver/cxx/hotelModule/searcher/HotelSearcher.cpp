/*
 * Author Artsiom Salauyou
 */

#include "HotelSearcher.hpp"

using namespace hotelModule;

HotelSearcher::HotelSearcher(ScMemoryContext *ms_context): context(ms_context){
    this->hotelTemplates = std::make_unique<HotelTemplates>();
}

ScAddr HotelSearcher::searchHotelByMinPricePerNight(const ScAddr & minPricePerNightAddr) {
    std::unique_ptr<ScTemplate> scTemplate = hotelTemplates->getHotelByMinPricePerNightTemplate(minPricePerNightAddr);
    if (scTemplate == SC_FALSE)
        SC_THROW_EXCEPTION(utils::ExceptionItemNotFound, "Hotel by min price per night template was not created");

    ScTemplateSearchResult scTemplateResult;
    context->HelperSearchTemplate(*scTemplate, scTemplateResult);

    if (scTemplateResult.IsEmpty())
        SC_THROW_EXCEPTION(utils::ExceptionInvalidParams, "No hotels found");

    ScTemplateSearchResultItem scTemplateSearchResultItem = scTemplateResult[0];
    ScAddr hotel = scTemplateSearchResultItem[HotelTemplates::HOTEL_ALIAS];

    return hotel;
}
