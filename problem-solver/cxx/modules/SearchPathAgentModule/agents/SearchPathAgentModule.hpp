#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "SearchFastestWayAgent.generated.hpp"

namespace SearchPathAgentModule
{

class SearchPathAgentModule : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_path, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

  static void findPath(
      ScAddr currentNode,
      ScAddr target,
      int currentLength,
      int& resultLength,
      std::vector<ScAddr>& currentPath,
      std::vector<ScAddr>& result);

  static std::list<ScAddr> getAllIncidentNodes(const ScAddr& node);

  static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

  static ScAddr getMinutesNode(const ScAddr& edge);

  static int getMinutesCount(ScAddr edge);

  static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
};

}  // namespace SearchPathAgentModule