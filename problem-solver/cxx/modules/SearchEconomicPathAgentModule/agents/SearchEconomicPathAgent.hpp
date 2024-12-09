#pragma once

#include <sc-memory/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
namespace SearchEconomicPathAgentModule
{

class SearchEconomicPathAgent : public ScActionInitiatedAgent
{
  public:
  ScAddr GetActionClass() const override;

  ScResult DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action) override;

  ScAddr GetEventSubscriptionElement() const override;

  static void findMinimalPath(
      ScAddr currentNode,
      ScAddr target,
      int currentLength,
      int& resultLength,
      std::vector<ScAddr>& currentPath,
      std::vector<ScAddr>& result);

  static std::list<ScAddr> getAllIncidentNodes(const ScAddr& node);

  static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

  static ScAddr getFuelNode(const ScAddr& edge);

  static int getFuelCost(ScAddr edge);

  static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
};

}  // namespace StreetSearchAgentModule
