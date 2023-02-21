#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "agent/AdministrativeFacility.hpp"
#include "agent/SoatoClassifier.hpp"
#include "keynodes/Keynodes.hpp"

#include "lib/csv.h"

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

  try
  {
    convertSoatoCodes();
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

void SoatoClassificationAgent::convertSoatoCodes()
{
  SoatoClassifier classifier;

  io::CSVReader<2> inTable(SOATO_CODES);
  inTable.read_header(io::ignore_extra_column, "СОАТО", "Наименование объекта");

  std::string code;
  std::string attr;

  while (inTable.read_row(code, attr))
  {
    const AdministrativeFacility facility = classifier.classify(std::make_pair(code, attr));
    sew(facility);
  }
}

// VillageSearchAgent is cool to check examples
void SoatoClassificationAgent::sew(const AdministrativeFacility & facility)
{
  ScAddr node = initializeFacility(facility);
  const std::vector<std::string> & categories = facility.getCategories();

  for (const auto & category : categories)
  {
    addToClassIfNotPresent(node, category);
  }
}

ScAddr SoatoClassificationAgent::initializeFacility(const AdministrativeFacility & facility)
{
  const auto & name = facility.getName();
  auto node = ms_context->HelperResolveSystemIdtf(name, ScType::Node);

  auto code = ms_context->HelperResolveSystemIdtf(facility.getCode(), ScType::Node);
  addToClassIfNotPresent(node, "код СОАТО");
  ms_context->CreateEdge(ScType::EdgeUCommon, node, code);

  return node;
}

void SoatoClassificationAgent::addToClassIfNotPresent(ScAddr node, const string & class_name)
{
  auto sc_class = ms_context->HelperResolveSystemIdtf(class_name, ScType::NodeClass);
  auto iterator = ms_context->Iterator3(sc_class, ScType::EdgeAccess, node);
  
  if (!iterator->Next())
  {
    ms_context->CreateEdge(ScType::EdgeAccess, sc_class, node);
  }
}

}  // namespace soatoClassificationModule
