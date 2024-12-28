/*
 * Author Artsiom Salauyou
 */

#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/HotelKeynodes.hpp"

#include "GetHotelByMinPricePerNightAgent.hpp"

using namespace hotelModule;

ScAddr GetHotelByMinPricePerNightAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return HotelKeynodes::action_get_hotel_by_min_price_per_night;
}

// ScResult GetHotelByMinPricePerNightAgent::DoProgram(ScActionInitiatedEvent const & event, ScAction & action)
ScResult GetHotelByMinPricePerNightAgent::DoProgram(ScAction & action)
{
  auto const & [priceLink] = action.GetArguments<1>();

  if (!m_context.IsElement(priceLink))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  // if (checkActionClass(actionAddr) == SC_FALSE)
  //   return action.FinishSuccessfully();

  ScAddr answerNode = m_context.GenerateNode(ScType::NodeConstStruct);

  ScAddrVector minPricesPerNight = getPricesLinks(&m_context, priceLink);

  ScAddrVector answerVector;
  initFields();

  try
  {
    ScAddr hotel;
    if (!minPricesPerNight.empty())
    {
      for (ScAddr minPricePerNight : minPricesPerNight)
      {
        hotel = hotelSearcher->searchHotelByMinPricePerNight(minPricePerNight);
        if (isHotel(&m_context, hotel))
          SC_AGENT_LOG_DEBUG("Hotel: ");
          answerVector.push_back(hotel);
      }
    }
    else
      SC_AGENT_LOG_WARNING("No hotels found");

    for (ScAddr findHotel : answerVector)
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answerNode, findHotel);
    }
  }
  catch (utils::ScException &)
  {

//todo(codegen-removal): replace AgentUtils:: usage
    // utils::AgentUtils::usage(&m_context, actionAddr, answerVector, false);
    
    
    return action.FinishUnsuccessfully();
  }

//todo(codegen-removal): replace AgentUtils:: usage
  // utils::AgentUtils::usage(&m_context, actionAddr, answerVector, true);
  
  action.SetResult(answerNode);
  return action.FinishSuccessfully();
}


void GetHotelByMinPricePerNightAgent::initFields()
{
  this->hotelSearcher = std::make_unique<HotelSearcher>(&m_context);
}

bool GetHotelByMinPricePerNightAgent::checkActionClass(const ScAddr & actionNode)
{
  return m_context.CheckConnector(
      HotelKeynodes::action_get_hotel_by_min_price_per_night, actionNode, ScType::ConstPermPosArc);
}

ScAddrVector GetHotelByMinPricePerNightAgent::getPricesLinks(ScMemoryContext * memory_ctx, const ScAddr & inputLink)
{
  auto minPriceLinkContent = memory_ctx->GetLinkContent(inputLink);
//todo(codegen-removal): method has signature changed
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
