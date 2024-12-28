/*
 * Author Artsiom Salauyou
 */

#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/HotelKeynodes.hpp"

#include "GetHotelByMinPricePerNightAgent.hpp"

using namespace hotelModule;

ScAddr GetHotelByMinPricePerNightAgent::GetActionClass() const // Метод получения класса действия агента
{

  return HotelKeynodes::action_get_hotel_by_min_price_per_night;
}

ScResult GetHotelByMinPricePerNightAgent::DoProgram(ScAction & action) // Главный метод агента 
{
  auto const & [priceLink] = action.GetArguments<1>();

  // Проверка наличия аргумента
  if (!m_context.IsElement(priceLink))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  ScAddr answerNode = m_context.GenerateNode(ScType::NodeConstStructure );

  ScAddrVector minPricesPerNight = getPricesLinks(&m_context, priceLink);

  ScAddrVector answerVector;
  initFields();

  try
  {
    ScAddr hotel;

    // Проверка вектора минимальных цен за ночь на не пустоту
    if (!minPricesPerNight.empty())
    {

      for (ScAddr minPricePerNight : minPricesPerNight)
      {
        hotel = hotelSearcher->searchHotelByMinPricePerNight(minPricePerNight);

        // Проверка является ли найденный узел отелем
        if (isHotel(&m_context, hotel))
          SC_AGENT_LOG_DEBUG("Hotel: ");
          answerVector.push_back(hotel);
      }
    }
    else
      SC_AGENT_LOG_WARNING("No hotels found");

    // Цикл для добавления найденных отелей в структуру ответа
    for (ScAddr findHotel : answerVector)
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answerNode, findHotel);
    }
  }
  catch (utils::ScException &)
  {
    return action.FinishUnsuccessfully();
  }


  
  
  action.SetResult(answerNode); 
  return action.FinishSuccessfully();
}


void GetHotelByMinPricePerNightAgent::initFields() // Метод для инициализации класса поиска отелей
{
  this->hotelSearcher = std::make_unique<HotelSearcher>(&m_context);
}

bool GetHotelByMinPricePerNightAgent::checkActionClass(const ScAddr & actionNode) 
{
  return m_context.CheckConnector(
      HotelKeynodes::action_get_hotel_by_min_price_per_night, actionNode, ScType::ConstPermPosArc);
}

ScAddrVector GetHotelByMinPricePerNightAgent::getPricesLinks(ScMemoryContext * memory_ctx, const ScAddr & inputLink) // Метод для получения цен
{
  auto minPriceLinkContent = memory_ctx->GetLinkContent(inputLink);

  ScAddrSet links = memory_ctx->SearchLinksByContent(minPriceLinkContent);

  ScAddrVector resultVector;
  for (ScAddr link : links)
  {
    if (isPriceLink(memory_ctx, link) && link != inputLink)
      resultVector.push_back(link);
  }
  return resultVector;
}

bool GetHotelByMinPricePerNightAgent::isHotel(ScMemoryContext * memory_ctx, const ScAddr & hotel)
{
  return (memory_ctx->CheckConnector(HotelKeynodes::concept_hotel, hotel, ScType::ConstPermPosArc) && 
          memory_ctx->CheckConnector(HotelKeynodes::concept_map_object, hotel, ScType::ConstPermPosArc));
}

bool GetHotelByMinPricePerNightAgent::isPriceLink(ScMemoryContext * memory_ctx, const ScAddr & priceLink)
{
  return (memory_ctx->CheckConnector(HotelKeynodes::concept_price, priceLink, ScType::ConstPermPosArc) && 
          memory_ctx->CheckConnector(HotelKeynodes::concept_usd, priceLink, ScType::ConstPermPosArc));
}
