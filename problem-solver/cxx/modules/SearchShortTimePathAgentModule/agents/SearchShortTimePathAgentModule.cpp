#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "SearchShortTimePathAgent.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace SearchShortTimePathAgentModule
{

SC_AGENT_IMPLEMENTATION(SearchShortTimePathAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  SC_LOG_INFO("SearchShortTimePathAgent begin");
  ScAddr actionNode = ms_context->GetEdgeTarget(edgeAddr);

  ScAddr const & startNodeAddr
      = IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!startNodeAddr.IsValid())
  {
    SC_LOG_ERROR("First parameter isn't valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr const & endNodeAddr
      = IteratorUtils::getFirstByOutRelation(&m_memoryCtx, actionNode, scAgentsCommon::CoreKeynodes::rrel_2);
  if (!endNodeAddr.IsValid())
  {
    SC_LOG_ERROR("Second parameter isn't valid.");
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }

  ScAddr const & answer = ms_context->CreateNode(ScType::NodeConstStruct);

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
    auto edge = getEdgeBetween(fromNode, toNode, ScType::EdgeUCommonConst, true);

    auto fromNodeMeta = getIdentifierMeta(fromNode);
    auto toNodeMeta = getIdentifierMeta(toNode);

    auto timeNode = getTimeNode(edge);

    auto edgeTotimeNode = getEdgeBetween(edge, timeNode, ScType::EdgeAccessConstPosPerm, false);
    auto timeNodeMeta = getIdentifierMeta(timeNode);

    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, fromNode);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, toNode);

    for (auto item : fromNodeMeta)
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, item);
    }

    for (auto item : toNodeMeta)
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, item);
    }

    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, timeNode);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edgeTotimeNode);

    for (auto item : timeNodeMeta)
    {
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, item);
    }
  }

  AgentUtils::finishAgentWork(ms_context.get(), actionNode, answer);
  SC_LOG_INFO("SearchShortTimePathAgent end");
  return SC_RESULT_OK;
}

void SearchShortTimePathAgent::findMinimalPath(
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
    auto edge = getEdgeBetween(currentNode, incidentNode, ScType::EdgeUCommonConst, true);
    auto timeCost = getTimeCost(edge);

    findMinimalPath(incidentNode, target, currentLength + timeCost, resultLength, currentPath, result);
  }

  currentPath.pop_back();
}

std::list<ScAddr> SearchShortTimePathAgent::getAllIncidentNodes(const ScAddr& node)
{
  std::list<ScAddr> result;

  auto iteratorForward = ms_context->Iterator3(
      node,
      ScType::EdgeUCommonConst,
      ScType::NodeConst);

  while (iteratorForward->Next())
  {
    result.push_back(iteratorForward->Get(2));
  }

  auto iteratorBackward = ms_context->Iterator3(
      ScType::NodeConst,
      ScType::EdgeUCommonConst,
      node);

  while (iteratorBackward->Next())
  {
    result.push_back(iteratorBackward->Get(0));
  }

  return result;
}

std::list<ScAddr> SearchShortTimePathAgent::getIdentifierMeta(const ScAddr& addr)
{
  auto iterator = ms_context->Iterator5(addr, ScType::EdgeDCommonConst, ScType::LinkConst, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_main_idtf);

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

int SearchShortTimePathAgent::getTimeCost(ScAddr edge)
{
  auto timeNode = getTimeNode(edge);
  auto idtf = CommonUtils::getMainIdtf(ms_context.get(), timeNode);

  return std::stoi(idtf);
}

ScAddr SearchShortTimePathAgent::getTimeNode(const ScAddr& edge)
{
  auto iterator = ms_context->Iterator3(ScType::NodeConst, ScType::EdgeAccessConstPosPerm, edge);

  while (iterator->Next())
  {
    auto timeNode = iterator->Get(0);

    if (!ms_context->HelperCheckEdge(Keynodes::concept_parameter, timeNode, ScType::EdgeAccessConstPosPerm))
    {
      continue;
    }

    return timeNode;
  }

  return ScAddr::Empty;
}

ScAddr SearchShortTimePathAgent::getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse)
{
  auto iterator = ms_context->Iterator3(from, type, to);

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
