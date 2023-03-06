#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "SearchMinPathAgent.generated.hpp"

namespace SearchMinPathAgentModule
{

struct Node
{
  bool isVisited;
  ScAddr addrNode;
  int minDistanceTag;
  std::vector<Node*> connectedNodes;
};

class SearchMinPathAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_search_min_path, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

  Node * getNodeFromNodesVectorByScAddr(const ScAddr & scAddr, std::vector<Node *> & nodesVector);
  int getDistanceBetweenNodes(ScMemoryContext * ms_context, const ScAddr & firstNode, const ScAddr & secondNode);
  std::vector<ScAddr> getConnectedCrossroads(ScMemoryContext * ms_context, const ScAddr & node);
  void setMinDistanceTags(ScMemoryContext * ms_context, Node * startNode);
  void getMinPath(ScMemoryContext * ms_context, std::vector<Node *> & resultNodesVector, Node * currentNode);
};

}
