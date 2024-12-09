/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include <sc-memory/sc_stream.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/GenerationUtils.hpp>
#include"sc-memory/sc_memory.hpp"
#include <iostream>
#include "VillageSearchAgent.hpp"

using namespace std;
using namespace utils;

namespace VillagesModule
{

ScAddr getVillageNode(ScLog * logger, std::unique_ptr<ScMemoryContext> & ms_context, ScAddr set)
{
  ScAddr answer = ms_context->GenerateNode(ScType::ConstNodeStructure);
  ScAddr first = ms_context->SearchElementBySystemIdentifier("nrel_Vitebsk_village");
  logger->Message(ScLog::Type::Info, "Villages Vitebsk " + ms_context->GetElementSystemIdentifier(set));

  ScIterator5Ptr iter =
      ms_context->CreateIterator5(set, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, first);
  while (iter->Next())
  {
    SC_LOG_ERROR("Found Vitebsk village");
    logger->Message(ScLog::Type::Info, "Village: " + ms_context->GetElementSystemIdentifier(iter->Get(2)));
    ms_context->GenerateConnector(ScType::ConstPermPosArc, answer, iter->Get(2));
    return answer;
  }
  logger->Message(ScLog::Type::Info, "village not found");

  return answer;
}

ScResult VillageSearchAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
{
  ScAgentContext ms_context;
  SC_AGENT_LOG_ERROR("started");
  ScLog * logger = ScLog::GetInstance();

  if (!event.GetArc().IsValid())
    return action.FinishUnsuccessfully();

  ScAddr questionNode = ms_context.GetArcTargetElement(event.GetArc());

  ScAddr node = IteratorUtils::getAnyFromSet(&ms_context, questionNode);
  if (!node.IsValid())
  {
    SC_AGENT_LOG_ERROR("Arg not found");
    return action.FinishUnsuccessfully();
  }
  std::unique_ptr<ScMemoryContext> context;
  ScAddr answer = getVillageNode(logger, context, node);

  ScAddr edgeToAnswer = ms_context.GenerateConnector(ScType::ConstCommonArc, questionNode, answer);
  action.SetResult(answer);

  return action.FinishSuccessfully();
}

ScAddr VillageSearchAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::question_vitebskVillage;
}

ScAddr VillageSearchAgent::GetEventSubscriptionElement() const
{
  return ScKeynodes::action_initiated;;
}
}  // namespace VillagesModule
