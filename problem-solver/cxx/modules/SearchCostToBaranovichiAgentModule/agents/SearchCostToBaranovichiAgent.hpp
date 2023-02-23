#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "SearchCostToBaranovichiAgent.generated.hpp"

namespace SearchCostToBaranovichiAgentModule
{

class SearchCostToBaranovichiAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_search_how_much_cost_to_go_to_Baranovichi, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

  static void findMinimalCost(
      ScAddr currentNode,
      ScAddr target,
      int currentLength,
      int& resultLength,
      std::vector<ScAddr>& currentPath,
      std::vector<ScAddr>& result);

  static std::list<ScAddr> getAllIncidentNodes(const ScAddr& node);

  static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

  static ScAddr getMoneyNode(const ScAddr& edge);

  static int getMoneyValue(ScAddr edge);

  static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
};

}  // namespace StreetSearchAgentModule
