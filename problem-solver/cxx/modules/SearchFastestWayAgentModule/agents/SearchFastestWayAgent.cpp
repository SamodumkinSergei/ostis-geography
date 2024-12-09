#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-memory/sc_memory.hpp"
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "SearchFastestWayAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace SearchFastestWayAgentModule
{

ScResult SearchFastestWayAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("begin");
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  ScAddr const & startNodeAddr
      = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);
  if (!startNodeAddr.IsValid())
  {
    SC_AGENT_LOG_ERROR("First parameter isn't valid.");
//todo(codegen-removal): replace AgentUtils:: usage
    //AgentUtils::finishAgentWork(&m_context, actionNode, false);
    return action.FinishUnsuccessfully();
  }

  ScAddr const & endNodeAddr
      = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_2);
  if (!endNodeAddr.IsValid())
  {
    SC_AGENT_LOG_ERROR("Second parameter isn't valid.");
//todo(codegen-removal): replace AgentUtils:: usage
    //AgentUtils::finishAgentWork(&m_context, actionNode, false);
    return action.FinishUnsuccessfully();
  }

  ScAddr const & answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  std::vector<ScAddr> result;

  {
    int length = INT32_MAX;
    std::vector<ScAddr> currentPath;

    findMinimalPath(startNodeAddr, endNodeAddr, 0, length, currentPath, result,m_context);
  }

  for (int i = 1; i < result.size(); ++i)
  {
    auto fromNode = result[i - 1];
    auto toNode = result[i];
    auto edge = getEdgeBetween(fromNode, toNode, ScType::ConstCommonEdge, true,m_context);

    auto fromNodeMeta = getIdentifierMeta(fromNode,m_context);
    auto toNodeMeta = getIdentifierMeta(toNode,m_context);

    auto minutesNode = getMinutesNode(edge,m_context);

    auto edgeToMinutesNode = getEdgeBetween(edge, minutesNode, ScType::ConstPermPosArc, false,m_context);
    auto minutesNodeMeta = getIdentifierMeta(minutesNode,m_context);

    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, fromNode);
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, edge);
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, toNode);

    for (auto item : fromNodeMeta)
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, item);
    }

    for (auto item : toNodeMeta)
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, item);
    }

    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, minutesNode);
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, edgeToMinutesNode);

    for (auto item : minutesNodeMeta)
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, item);
    }
  }
  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  m_context.GenerateConnector(ScType::ConstPermPosArc,ScKeynodes::nrel_result, edgeToAnswer);

 action.SetResult(answer);
  SC_AGENT_LOG_INFO("end");
  return action.FinishSuccessfully();
}

ScAddr SearchFastestWayAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::action_search_fastest_way;
}

ScAddr SearchFastestWayAgent::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

void SearchFastestWayAgent::findMinimalPath(
    ScAddr currentNode,
    ScAddr target,
    int currentLength,
    int& resultLength,
    std::vector<ScAddr>& currentPath,
    std::vector<ScAddr>& result, ScAgentContext& m_context)
{
  if (std::find(currentPath.begin(), currentPath.end(), currentNode) != currentPath.end())
  {
    return;
  }

  currentPath.push_back(currentNode);

  if (currentNode == target)
  {
    if (currentLength < resultLength)
    {
      result = std::vector<ScAddr>(currentPath);
      resultLength = currentLength;

      currentPath.pop_back();
      return;
    }
  }

  auto incidentNodes = getAllIncidentNodes(currentNode, m_context);

  for (auto incidentNode : incidentNodes)
  {
    auto edge = getEdgeBetween(currentNode, incidentNode, ScType::ConstCommonEdge, true,m_context);
    auto minutesCount = getMinutesCount(edge,m_context);

    findMinimalPath(incidentNode, target, currentLength + minutesCount, resultLength, currentPath, result,m_context);
  }

  currentPath.pop_back();
}

std::list<ScAddr> SearchFastestWayAgent::getAllIncidentNodes(const ScAddr& node, ScAgentContext& m_context)
{
  std::list<ScAddr> result;

  auto iteratorForward = m_context.CreateIterator3(
      node,
      ScType::ConstCommonEdge,
      ScType::ConstNode);

  while (iteratorForward->Next())
  {
    result.push_back(iteratorForward->Get(2));
  }

  auto iteratorBackward = m_context.CreateIterator3(
      ScType::ConstNode,
      ScType::ConstCommonEdge,
      node);

  while (iteratorBackward->Next())
  {
    result.push_back(iteratorBackward->Get(0));
  }

  return result;
}

std::list<ScAddr> SearchFastestWayAgent::getIdentifierMeta(const ScAddr& addr, ScAgentContext& m_context)
{
  auto iterator = m_context.CreateIterator5(addr, ScType::ConstCommonArc, ScType::ConstNodeLink, ScType::ConstPermPosArc, Keynodes::nrel_main_idtf);

  if (iterator->Next())
  {
    return std::list<ScAddr> {
        iterator->Get(1),
        iterator->Get(2),
        iterator->Get(3),
        iterator->Get(4)
    };
  }

  return {};
}

int SearchFastestWayAgent::getMinutesCount(ScAddr edge, ScAgentContext& m_context)
{
  auto minutesNode = getMinutesNode(edge,m_context);
  auto idtf = CommonUtils::getMainIdtf(&m_context, minutesNode);
try{
  return std::stoi(idtf);
}
catch(const std::invalid_argument& e){
  return 0;
}
}

ScAddr SearchFastestWayAgent::getMinutesNode(const ScAddr& edge, ScAgentContext& m_context)
{

  auto iterator = m_context.CreateIterator3(ScType::ConstNode, ScType::ConstPermPosArc, edge);

  while (iterator->Next())
  {
    auto minutesNode = iterator->Get(0);

    if (!m_context.CheckConnector(Keynodes::concept_parameter, minutesNode, ScType::ConstPermPosArc))
    {
      continue;
    }

    return minutesNode;
  }

  return ScAddr::Empty;
}

ScAddr SearchFastestWayAgent::getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse, ScAgentContext& m_context)
{
  auto iterator = m_context.CreateIterator3(from, type, to);

  if (iterator->Next())
  {
    return iterator->Get(1);
  }

  if (findReverse)
  {
    return getEdgeBetween(to, from, type, false,m_context);
  }
  return ScAddr:: Empty;
}

}  // namespace SearchFastestWayAgentModule
