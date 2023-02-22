#pragma once

#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "sc-memory/kpm/sc_agent.hpp"

#include "SoatoClassificationAgent.generated.hpp"

namespace soatoClassificationModule
{

class AdministrativeFacility;

class SoatoClassificationAgent : public ScAgent
{
  SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY();

private:
  bool checkActionClass(ScAddr const & actionAddr);

  void convertSoatoCodes();

  void sew(const AdministrativeFacility & facility);

  ScAddr initializeFacility(const AdministrativeFacility & facility);

  void addToClassIfNotPresent(ScAddr node, const std::string & class_name);

  ScAddr createEdgeIfNotPresent(const ScAddr & begin, const ScAddr & end, const ScType & type);
};

}  // namespace soatoClassificationModule
