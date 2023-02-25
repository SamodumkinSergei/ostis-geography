#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "FindingTimeToGetToMinskAgent.generated.hpp"

namespace FindingTimeToGetToMinskAgentModule
{

class FindingTimeToGetToMinskAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_finding_time_to_get_to_minsk, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

  static void findTime(
      ScAddr currentNode,
      ScAddr target,
      int currentLength,
      int& resultLength,
      std::vector<ScAddr>& currentPath,
      std::vector<ScAddr>& result);

  static std::list<ScAddr> getAllIncidentNodes(const ScAddr& node);

  static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

  static ScAddr getTimeNode(const ScAddr& edge);

  static int getTimeCost(ScAddr edge);

  static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
};

}  // namespace FindingTimeToGetToMinskAgent
