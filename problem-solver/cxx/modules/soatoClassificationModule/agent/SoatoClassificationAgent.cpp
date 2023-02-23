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
  std::string name;

  while (inTable.read_row(code, name))
  {
    const AdministrativeFacility facility = classifier.classify(std::make_pair(code, name));
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
  auto facilityNode = ms_context->HelperResolveSystemIdtf(name, ScType::NodeConst);

  //Adding facility node into ATE class
  addToClassIfNotPresent(facilityNode, "АТЕ");

  const auto & code = facility.getCode();
  auto codeNode = ms_context->HelperResolveSystemIdtf(code, ScType::NodeConst);

  //Adding code node into "SOATO code" class
  addToClassIfNotPresent(codeNode, "код СОАТО");

  //Resolving d-common edge from facility to code
  auto facilityToCodeEdge = createEdgeIfNotPresent(facilityNode, codeNode, ScType::EdgeDCommonConst);

  //Resolving "SOATO code" relation
  auto codeNoRole = ms_context->HelperResolveSystemIdtf("код СОАТО*", ScType::NodeConstNoRole);

  //Creating access edge from "SOATO code" relation to d-common-edge between facility to code
  createEdgeIfNotPresent(codeNoRole, facilityToCodeEdge, ScType::EdgeAccessConstPosPerm);

  return facilityNode;
}

void SoatoClassificationAgent::addToClassIfNotPresent(ScAddr node, const string & className)
{
  auto scClass = ms_context->HelperResolveSystemIdtf(className, ScType::NodeConstClass);
  createEdgeIfNotPresent(scClass, node, ScType::EdgeAccessConstPosPerm);
}

ScAddr SoatoClassificationAgent::createEdgeIfNotPresent(const ScAddr & begin, const ScAddr & end, const ScType & type) {
  auto edgeIsPresent = m_memoryCtx.HelperCheckEdge(begin, end, type);
  if (!edgeIsPresent)
  {
    return ms_context->CreateEdge(type, begin, end);
  }
}

}  // namespace soatoClassificationModule
