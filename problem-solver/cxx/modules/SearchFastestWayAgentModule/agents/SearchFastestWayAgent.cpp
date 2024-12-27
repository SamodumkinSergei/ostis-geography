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

// Основная функция, реализующая логику агента
ScResult SearchFastestWayAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  // Проверяем, является ли дуга события валидной
  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  SC_AGENT_LOG_INFO("начало");
  
  // Получаем узел действия, вызвавший событие
  ScAddr actionNode = m_context.GetArcTargetElement(event.GetArc());

  // Извлекаем начальный узел из первого параметра действия
  ScAddr const & startNodeAddr
      = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_1);
  if (!startNodeAddr.IsValid())
  {
    SC_AGENT_LOG_ERROR("Первый параметр невалиден.");
    return action.FinishUnsuccessfully();
  }

  // Извлекаем конечный узел из второго параметра действия
  ScAddr const & endNodeAddr
      = IteratorUtils::getAnyByOutRelation(&m_context, actionNode, ScKeynodes::rrel_2);
  if (!endNodeAddr.IsValid())
  {
    SC_AGENT_LOG_ERROR("Второй параметр невалиден.");
    return action.FinishUnsuccessfully();
  }

  // Создаем узел для хранения результата поиска
  ScAddr const & answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  // Вектор для хранения кратчайшего пути
  std::vector<ScAddr> result;

  {
    // Инициализируем переменные для хранения минимального пути и его длины
    int length = INT32_MAX;
    std::vector<ScAddr> currentPath;

    // Поиск кратчайшего пути с использованием рекурсии
    findMinimalPath(startNodeAddr, endNodeAddr, 0, length, currentPath, result, m_context);
  }

  // Обрабатываем найденный путь и генерируем связи для визуализации результата
  for (int i = 1; i < result.size(); ++i)
  {
    auto fromNode = result[i - 1];
    auto toNode = result[i];
    auto edge = getEdgeBetween(fromNode, toNode, ScType::ConstCommonEdge, true, m_context);

    // Получаем метаданные для узлов и их связей
    auto fromNodeMeta = getIdentifierMeta(fromNode, m_context);
    auto toNodeMeta = getIdentifierMeta(toNode, m_context);

    // Получаем узел, представляющий время пути в минутах
    auto minutesNode = getMinutesNode(edge, m_context);

    auto edgeToMinutesNode = getEdgeBetween(edge, minutesNode, ScType::ConstPermPosArc, false, m_context);
    auto minutesNodeMeta = getIdentifierMeta(minutesNode, m_context);

    // Создаем связи в результирующем узле
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

  // Связываем результат с узлом действия через общую дугу
  ScAddr edgeToAnswer = m_context.GenerateConnector(ScType::ConstCommonArc, actionNode, answer);
  m_context.GenerateConnector(ScType::ConstPermPosArc, ScKeynodes::nrel_result, edgeToAnswer);

  action.SetResult(answer);
  SC_AGENT_LOG_INFO("конец");
  return action.FinishSuccessfully();
}

// Определяем класс действия, которое обрабатывается этим агентом
ScAddr SearchFastestWayAgent::GetActionClass() const
{
  return Keynodes::action_search_fastest_way;
}

// Указываем элемент, на который подписывается агент
ScAddr SearchFastestWayAgent::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;
}

// Рекурсивный поиск минимального пути между узлами
void SearchFastestWayAgent::findMinimalPath(
    ScAddr currentNode,
    ScAddr target,
    int currentLength,
    int& resultLength,
    std::vector<ScAddr>& currentPath,
    std::vector<ScAddr>& result,
    ScAgentContext& m_context)
{
  // Проверяем, если узел уже был в пути, выходим
  if (std::find(currentPath.begin(), currentPath.end(), currentNode) != currentPath.end())
  {
    return;
  }

  currentPath.push_back(currentNode);

  // Если текущий узел совпадает с целевым
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

  // Получаем соседние узлы
  auto incidentNodes = getAllIncidentNodes(currentNode, m_context);

  for (auto incidentNode : incidentNodes)
  {
    auto edge = getEdgeBetween(currentNode, incidentNode, ScType::ConstCommonEdge, true, m_context);
    auto minutesCount = getMinutesCount(edge, m_context);

    findMinimalPath(incidentNode, target, currentLength + minutesCount, resultLength, currentPath, result, m_context);
  }

  currentPath.pop_back();
}

// Получение всех соседних узлов для заданного узла
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

// Получение метаданных для заданного узла
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

// Получение времени в минутах из дуги
int SearchFastestWayAgent::getMinutesCount(ScAddr edge, ScAgentContext& m_context)
{
  auto minutesNode = getMinutesNode(edge, m_context);
  auto idtf = CommonUtils::getMainIdtf(&m_context, minutesNode);
  try
  {
    return std::stoi(idtf);
  }
  catch (const std::invalid_argument& e)
  {
    return 0;
  }
}

// Получение узла времени пути из дуги
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

// Получение дуги между двумя узлами
ScAddr SearchFastestWayAgent::getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse, ScAgentContext& m_context)
{
  auto iterator = m_context.CreateIterator3(from, type, to);

  if (iterator->Next())
  {
    return iterator->Get(1);
  }

  if (findReverse)
  {
    return getEdgeBetween(to, from, type, false, m_context);
  }
  return ScAddr::Empty;
}

}  // namespace SearchFastestWayAgentModule
