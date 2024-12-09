#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-memory/sc_memory.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "SearchEconomicPathAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace SearchEconomicPathAgentModule
{

ScResult SearchEconomicPathAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  ScAgentContext m_context; 
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

    findMinimalPath(startNodeAddr, endNodeAddr, 0, length, currentPath, result);
  }

  for (int i = 1; i < result.size(); ++i)
  {
    auto fromNode = result[i - 1];
    auto toNode = result[i];
    auto edge = getEdgeBetween(fromNode, toNode, ScType::ConstCommonEdge, true);

    auto fromNodeMeta = getIdentifierMeta(fromNode);
    auto toNodeMeta = getIdentifierMeta(toNode);

    auto fuelNode = getFuelNode(edge);

    auto edgeToFuelNode = getEdgeBetween(edge, fuelNode, ScType::ConstPermPosArc, false);
    auto fuelNodeMeta = getIdentifierMeta(fuelNode);

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

    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, fuelNode);
    m_context.GenerateConnector(ScType::ConstPermPosArc, answer, edgeToFuelNode);

    for (auto item : fuelNodeMeta)
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, item);
    }
  }

  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  action.SetResult(answer);
  SC_AGENT_LOG_INFO("end");
  return action.FinishSuccessfully();
}

ScAddr SearchEconomicPathAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::action_search_economic_path;
}

ScAddr SearchEconomicPathAgent::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;;
}

void SearchEconomicPathAgent::findMinimalPath(
    ScAddr currentNode,
    ScAddr target,
    int currentLength,
    int& resultLength,
    std::vector<ScAddr>& currentPath,
    std::vector<ScAddr>& result)
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

  auto incidentNodes = getAllIncidentNodes(currentNode);

  for (auto incidentNode : incidentNodes)
  {
    auto edge = getEdgeBetween(currentNode, incidentNode, ScType::ConstCommonEdge, true);
    auto fuelCost = getFuelCost(edge);

    findMinimalPath(incidentNode, target, currentLength + fuelCost, resultLength, currentPath, result);
  }

  currentPath.pop_back();
}

std::list<ScAddr> SearchEconomicPathAgent::getAllIncidentNodes(const ScAddr& node)
{
  ScAgentContext ms_context;
  std::list<ScAddr> result;

  auto iteratorForward = ms_context.CreateIterator3(
      node,
      ScType::ConstCommonEdge,
      ScType::ConstNode);

  while (iteratorForward->Next())
  {
    result.push_back(iteratorForward->Get(2));
  }

  auto iteratorBackward = ms_context.CreateIterator3(
      ScType::ConstNode,
      ScType::ConstCommonEdge,
      node);

  while (iteratorBackward->Next())
  {
    result.push_back(iteratorBackward->Get(0));
  }

  return result;
}

std::list<ScAddr> SearchEconomicPathAgent::getIdentifierMeta(const ScAddr& addr)
{
  ScAgentContext ms_context;
  auto iterator = ms_context.CreateIterator5(addr, ScType::ConstCommonArc, ScType::ConstNodeLink, ScType::ConstPermPosArc, Keynodes::nrel_main_idtf);

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

int SearchEconomicPathAgent::getFuelCost(ScAddr edge)
{ 
  ScAgentContext ms_context;
  auto fuelNode = getFuelNode(edge);
  auto idtf = CommonUtils::getMainIdtf(&ms_context, fuelNode);

  return std::stoi(idtf);
}

ScAddr SearchEconomicPathAgent::getFuelNode(const ScAddr& edge)
{
  ScAgentContext ms_context;
  auto iterator = ms_context.CreateIterator3(ScType::ConstNode, ScType::ConstPermPosArc, edge);

  while (iterator->Next())
  {
    auto fuelNode = iterator->Get(0);

    if (!ms_context.CheckConnector(Keynodes::concept_parameter, fuelNode, ScType::ConstPermPosArc))
    {
      continue;
    }

    return fuelNode;
  }

  return ScAddr::Empty;
}

ScAddr SearchEconomicPathAgent::getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse)
{
  ScAgentContext ms_context;
  auto iterator = ms_context.CreateIterator3(from, type, to);

  if (iterator->Next())
  {
    return iterator->Get(1);
  }

  if (findReverse)
  {
    return getEdgeBetween(to, from, type, false);
  }
}

}  // namespace StreetSearchAgentModule
