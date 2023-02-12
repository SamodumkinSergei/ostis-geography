#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/Keynodes.hpp"

#include "SoatoClassificationAgent.hpp"

namespace soatoClassificationModule
{
SC_AGENT_IMPLEMENTATION(SoatoClassificationAgent)
{
  ScAddr actionAddr = otherAddr;
  if (!checkActionClass(actionAddr))
  {
    return SC_RESULT_OK;
  }

  SC_LOG_DEBUG("SoatoClassificationAgent: started");

  ScAddrVector answerElements;

  ScAddr const & messageAddr =
      utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!messageAddr.IsValid())
  {
    SC_LOG_ERROR("SoatoClassificationAgent: the message isn’t valid");
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    return SC_RESULT_ERROR;
  }

  try
  {
    // TODO: implement the agent logic here
  }
  catch (utils::ScException & exception)
  {
    SC_LOG_ERROR(exception.Description());
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerElements, false);
    SC_LOG_DEBUG("SoatoClassificationAgent: finished with an error");
    return SC_RESULT_ERROR;
  }

  utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerElements, true);
  SC_LOG_DEBUG("SoatoClassificationAgent: finished");
  return SC_RESULT_OK;
}

bool SoatoClassificationAgent::checkActionClass(ScAddr const & actionAddr)
{
  return m_memoryCtx.HelperCheckEdge(Keynodes::action_soato_classification, actionAddr, ScType::EdgeAccessConstPosPerm);
}

}  // namespace soatoClassificationModule
