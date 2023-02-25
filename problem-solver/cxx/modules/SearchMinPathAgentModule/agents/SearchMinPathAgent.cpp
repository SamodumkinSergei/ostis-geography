#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include "SearchMinPathAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace SearchMinPathAgentModule
{

SC_AGENT_IMPLEMENTATION(SearchMinPathAgent)
{
  if (!edgeAddr.IsValid())
  {
    return SC_RESULT_ERROR;
  }

  SC_LOG_INFO("SearchMinPathAgent begin");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  const ScAddr & startNodeAddr =
      IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!startNodeAddr.IsValid())
  {
    SC_LOG_ERROR("First node is not valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  const ScAddr& endNodeAddr =
      IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_2);
  if (!endNodeAddr.IsValid())
  {
    SC_LOG_ERROR("Second node is not valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  std::vector<Node *> nodesVector;
  auto iter3Road = ms_context->Iterator3(Keynodes::concept_road, ScType::EdgeAccessConstPosPerm, ScType::NodeConst);
  while (iter3Road->Next())
  {
    auto iter5ArrayOfCrossRoads = ms_context->Iterator5(
        iter3Road->Get(2),
        ScType::EdgeDCommonConst,
        ScType::NodeConst,
        ScType::EdgeAccessConstPosPerm,
        Keynodes::nrel_bordering_points);
    while (iter5ArrayOfCrossRoads->Next())
    {
      auto iter3NodeAddr =
          ms_context->Iterator3(iter5ArrayOfCrossRoads->Get(2), ScType::EdgeAccessConstPosPerm, ScType::NodeConst);
      while (iter3NodeAddr->Next())
      {
        if(getNodeFromNodesVectorByScAddr(iter3NodeAddr->Get(2), nodesVector) == NULL){
        Node * node = new Node;
        node->isVisited = false;
        node->addrNode = iter3NodeAddr->Get(2);
        node->minDistanceTag = INT32_MAX;

        nodesVector.push_back(node);
        }
      }
    }
  }

  for (int i = 0; i < nodesVector.size(); i++)
  {
    auto connectedCrossroadsVector = getConnectedCrossroads(ms_context.get(), nodesVector[i]->addrNode);
    for (int j = 0; j < connectedCrossroadsVector.size(); j++)
    {
      for (int k = 0; k < nodesVector.size(); k++)
      {
        if (connectedCrossroadsVector[j] == nodesVector[k]->addrNode)
        {
          nodesVector[i]->connectedNodes.push_back(nodesVector[k]);
          break;
        }
      }
    }
  }

  Node * firstNode;
  firstNode = getNodeFromNodesVectorByScAddr(startNodeAddr, nodesVector);

  firstNode->minDistanceTag = 0;
  setMinDistanceTags(ms_context.get(), firstNode);

  std::vector<Node *> resultNodesVector;

  Node * lastNode;
  lastNode = getNodeFromNodesVectorByScAddr(endNodeAddr, nodesVector);

  SC_LOG_INFO(lastNode->minDistanceTag);

  resultNodesVector.push_back(lastNode);
  getMinPath(ms_context.get(), resultNodesVector, lastNode);

  SC_LOG_INFO(resultNodesVector.size());

  ScAddr const & answer = ms_context->CreateNode(ScType::NodeConstStruct);

  auto resultArray = ms_context->CreateNode(ScType::NodeConst);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, resultArray);

  for(int i = 0, j = resultNodesVector.size(); i < resultNodesVector.size(); i++, j--) {
    auto edgeBetweenArrayAndNode =
        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, resultArray, resultNodesVector[i]->addrNode);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, resultNodesVector[i]->addrNode);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edgeBetweenArrayAndNode);
    auto iter5NodeIdth = ms_context->Iterator5(
        resultNodesVector[i]->addrNode,
        ScType::EdgeDCommonConst,
        ScType::Unknown,
        ScType::EdgeAccessConstPosPerm,
        Keynodes::nrel_main_idtf);
    while (iter5NodeIdth->Next())
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5NodeIdth->Get(1));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5NodeIdth->Get(2));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5NodeIdth->Get(3));
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5NodeIdth->Get(4));
    }

    auto rrelNodeNumber = ms_context->CreateNode(ScType::NodeConstRole);
    ms_context->HelperSetSystemIdtf(std::to_string(j) + "\'", rrelNodeNumber);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, rrelNodeNumber);

    auto edge = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, rrelNodeNumber, edgeBetweenArrayAndNode);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge);
  }

  AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
  SC_LOG_INFO("SearchMinPathAgent end");
  return SC_RESULT_OK;
}

Node* SearchMinPathAgent::getNodeFromNodesVectorByScAddr(const ScAddr& scAddr, std::vector<Node*>& nodesVector) {
  for (int i = 0; i < nodesVector.size(); i++)
  {
    if (nodesVector[i]->addrNode == scAddr)
    {
      return nodesVector[i];
    }
  }

  return NULL;
}

std::vector<ScAddr> SearchMinPathAgent::getConnectedCrossroads(ScMemoryContext * ms_context, const ScAddr & node)
{
  std::vector<ScAddr> connectedCrossroadsVector;

  auto iter3ArraysOfCrossroads = ms_context->Iterator3(ScType::NodeConst, ScType::EdgeAccessConstPosPerm, node);
  while (iter3ArraysOfCrossroads->Next())
  {
    auto iter5ArraysOfCrossroads = ms_context->Iterator5(
        ScType::NodeConst,
        ScType::EdgeDCommonConst,
        iter3ArraysOfCrossroads->Get(0),
        ScType::EdgeAccessConstPosPerm,
        Keynodes::nrel_bordering_points);
    while (iter5ArraysOfCrossroads->Next())
    {
      auto iter3crossroads =
          ms_context->Iterator3(iter5ArraysOfCrossroads->Get(2), ScType::EdgeAccessConstPosPerm, ScType::NodeConst);
      while (iter3crossroads->Next())
      {
        if (iter3crossroads->Get(2) != node)
        {
          connectedCrossroadsVector.push_back(iter3crossroads->Get(2));
        }
      }
    }
  }

  return connectedCrossroadsVector;
}

int SearchMinPathAgent::getDistanceBetweenNodes(
    ScMemoryContext * ms_context,
    const ScAddr & firstNode,
    const ScAddr & secondNode)
{
  ScAddr arrayOfCrossRoads = ScAddr::Empty;
  auto iter3arrayOfCrossRoads = ms_context->Iterator3(ScType::NodeConst, ScType::EdgeAccessConstPosPerm, firstNode);
  while (iter3arrayOfCrossRoads->Next())
  {
    auto iter5Road = ms_context->Iterator5(
        ScType::NodeConst,
        ScType::EdgeDCommonConst,
        iter3arrayOfCrossRoads->Get(0),
        ScType::EdgeAccessConstPosPerm,
        Keynodes::nrel_bordering_points);
    while (iter5Road->Next())
    {
      auto iter3SecondNode = ms_context->Iterator3(iter5Road->Get(2), ScType::EdgeAccessConstPosPerm, secondNode);
      while (iter3SecondNode->Next())
      {
        arrayOfCrossRoads = iter3SecondNode->Get(0);
      }
    }
  }
  ScAddr road = ScAddr::Empty;

  auto iter5Road = ms_context->Iterator5(
      ScType::NodeConst,
      ScType::EdgeDCommonConst,
      arrayOfCrossRoads,
      ScType::EdgeAccessConstPosPerm,
      Keynodes::nrel_bordering_points);
  while (iter5Road->Next())
  {
    road = iter5Road->Get(0);
  }
  ScAddr roadLength = ScAddr::Empty;
  auto iter3Length = ms_context->Iterator3(ScType::NodeConstClass, ScType::EdgeAccessConstPosPerm, road);
  while (iter3Length->Next())
  {
    auto iter3LengthType =
        ms_context->Iterator3(Keynodes::concept_length, ScType::EdgeAccessConstPosPerm, iter3Length->Get(0));
    while (iter3LengthType->Next())
    {
      roadLength = iter3Length->Get(0);
    }
  }
  string length = ms_context->HelperGetSystemIdtf(roadLength);
  return stoi(length);
}

void SearchMinPathAgent::setMinDistanceTags(ScMemoryContext * ms_context, Node * startNode)
{
  std::queue<Node *> queue;
  queue.push(startNode);

  while (!queue.empty())
  {
    auto currentNode = queue.front();
    queue.pop();

    for (int i = 0; i < currentNode->connectedNodes.size(); i++)
    {
      if (!currentNode->connectedNodes[i]->isVisited)
      {
        auto distanceTag =
            currentNode->minDistanceTag +
            getDistanceBetweenNodes(ms_context, currentNode->addrNode, currentNode->connectedNodes[i]->addrNode);
        currentNode->connectedNodes[i]->minDistanceTag =
            std::min(distanceTag, currentNode->connectedNodes[i]->minDistanceTag);
      }
    }
    currentNode->isVisited = true;
    std::sort(
        currentNode->connectedNodes.begin(), currentNode->connectedNodes.end(), [](const Node * lhs, const Node * rhs) {
          return lhs->minDistanceTag < rhs->minDistanceTag;
        });

    for (int i = 0; i < currentNode->connectedNodes.size(); i++)
    {
      if (!currentNode->connectedNodes[i]->isVisited)
      {
        queue.push(currentNode->connectedNodes[i]);
      }
    }
  }
}

void SearchMinPathAgent::getMinPath(
    ScMemoryContext * ms_context,
    std::vector<Node *> & resultNodesVector,
    Node * currentNode)
{
  Node * minDistanceNodeToAdd;

  for (int i = 0; i < currentNode->connectedNodes.size(); i++)
  {
    if (currentNode->minDistanceTag -
            getDistanceBetweenNodes(ms_context, currentNode->addrNode, currentNode->connectedNodes[i]->addrNode) ==
        currentNode->connectedNodes[i]->minDistanceTag)
    {
      minDistanceNodeToAdd = currentNode->connectedNodes[i];
      resultNodesVector.push_back(minDistanceNodeToAdd);
      break;
    }
  }

  if (minDistanceNodeToAdd->minDistanceTag == 0)
  {
    return;
  }

  getMinPath(ms_context, resultNodesVector, minDistanceNodeToAdd);
}
}
