#pragma once

#include <sc-memory/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
namespace SearchFastestWayAgentModule
{

class SearchFastestWayAgent : public ScActionInitiatedAgent
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
      std::vector<ScAddr>& result,ScAgentContext& m_context);

  static std::list<ScAddr> getAllIncidentNodes(const ScAddr& node,ScAgentContext& m_context);

  static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr,ScAgentContext& m_context);

  static ScAddr getMinutesNode(const ScAddr& edge,ScAgentContext& m_context);

  static int getMinutesCount(ScAddr edge,ScAgentContext& m_context);

  static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse,ScAgentContext& m_context);
};

}  // namespace SearchFastestWayAgentModule
