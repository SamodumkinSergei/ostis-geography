#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-memory/sc_memory.hpp"
#include "agent/AdministrativeFacility.hpp"
#include "agent/SoatoClassifier.hpp"
#include "keynodes/Keynodes.hpp"

#include "lib/csv.h"

#include "SoatoClassificationAgent.hpp"

namespace soatoClassificationModule
{

ScResult SoatoClassificationAgent::DoProgram(ScActionInitiatedEvent const & event, ScAction & action)
{
  ScAddr actionAddr = event.GetOtherElement();
  if (!checkActionClass(actionAddr))
  {
    return action.FinishSuccessfully();
  }

  SC_AGENT_LOG_DEBUG("started");

  ScAddrVector answerElements;

  try
  {
    convertSoatoCodes();
  }
  catch (utils::ScException & exception)
  {
    SC_AGENT_LOG_ERROR(exception.Description());
//todo(codegen-removal): replace AgentUtils:: usage
    //utils::AgentUtils::finishAgentWork(&m_context, actionAddr, answerElements, false);
    SC_AGENT_LOG_DEBUG("finished with an error");
    return action.FinishUnsuccessfully();
  }

  action.SetResult(answerElements[0]);
  SC_AGENT_LOG_DEBUG("finished");
  return action.FinishSuccessfully();
}

ScAddr SoatoClassificationAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return Keynodes::action_soato_classification;
}


bool SoatoClassificationAgent::checkActionClass(ScAddr const & actionAddr)
{
  return m_context.CheckConnector(Keynodes::action_soato_classification, actionAddr, ScType::ConstPermPosArc);
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
  ScAgentContext ms_context;
  const auto & name = facility.getName();
  auto facilityNode = ms_context.ResolveElementSystemIdentifier(name, ScType::ConstNode);

  //Adding facility node into ATE class
  addToClassIfNotPresent(facilityNode, "АТЕ");

  const auto & code = facility.getCode();
  auto codeNode = ms_context.ResolveElementSystemIdentifier(code, ScType::ConstNode);

  //Adding code node into "SOATO code" class
  addToClassIfNotPresent(codeNode, "код СОАТО");

  //Resolving d-common edge from facility to code
  auto facilityToCodeEdge = createEdgeIfNotPresent(facilityNode, codeNode, ScType::ConstCommonArc);

  //Resolving "SOATO code" relation
  auto codeNoRole = ms_context.ResolveElementSystemIdentifier("код СОАТО*", ScType::ConstNodeNonRole);

  //Creating access edge from "SOATO code" relation to d-common-edge between facility to code
  createEdgeIfNotPresent(codeNoRole, facilityToCodeEdge, ScType::ConstPermPosArc);

  return facilityNode;
}

void SoatoClassificationAgent::addToClassIfNotPresent(ScAddr node, const std::string & className)
{
  ScAgentContext ms_context;
  auto scClass = ms_context.ResolveElementSystemIdentifier(className, ScType::ConstNodeClass);
  createEdgeIfNotPresent(scClass, node, ScType::ConstPermPosArc);
}

ScAddr SoatoClassificationAgent::createEdgeIfNotPresent(const ScAddr & begin, const ScAddr & end, const ScType & type) {
  ScAgentContext ms_context;
  auto edgeIsPresent = m_context.CheckConnector(begin, end, type);
  if (!edgeIsPresent)
  {
    return ms_context.GenerateConnector(type, begin, end);
  }
}

}  // namespace soatoClassificationModule
