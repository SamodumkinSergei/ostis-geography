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
  ScAddr GetActionClass() const override; // Метод получения класса действий агента

  
  ScResult DoProgram(ScAction & action) override; // Главный метод агента

  
  

  

  

  private:
  std::unique_ptr<HotelSearcher> hotelSearcher;

  bool checkActionClass(ScAddr const & actionAddr); 

  static bool isHotel(ScMemoryContext * memory_ctx, ScAddr const & hotel);

  static bool isPriceLink(ScMemoryContext * memory_ctx, ScAddr const & priceLink);

  static ScAddrVector getPricesLinks(ScMemoryContext * memory_ctx, ScAddr const & InputLink); // Метод получения цен

  void initFields(); // Метод для инициализации класса поиска отелей
};
}  
