/*
 * Author Artsiom Salauyou
 */

#pragma once

#include "sc-memory/sc_agent.hpp"
#include "searcher/HotelSearcher.hpp"

namespace hotelModule
{
class GetHotelByMinPricePerNightAgent : public ScActionInitiatedAgent
{
  
  public:
  ScAddr GetActionClass() const override;

  // ScResult DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) const override;
  ScResult DoProgram(ScAction & action) override;

  // public:
  // ScAddr GetActionClass() const override;

  // ScAddr GetEventSubscriptionElement() const override;

  // ScResult DoProgram(ScActionInitiatedEvent const & event, ScAction & action) override;

  private:
  std::unique_ptr<HotelSearcher> hotelSearcher;

  bool checkActionClass(ScAddr const & actionAddr);

  static bool isHotel(ScMemoryContext * memory_ctx, ScAddr const & hotel);

  static bool isPriceLink(ScMemoryContext * memory_ctx, ScAddr const & priceLink);

  static ScAddrVector getPricesLinks(ScMemoryContext * memory_ctx, ScAddr const & InputLink);

  void initFields();
};
}  // namespace hotelModule
