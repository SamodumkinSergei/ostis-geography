#pragma once

#include "sc-memory/sc_agent.hpp"

namespace soatoClassificationModule
{

class AdministrativeFacility;

class SoatoClassificationAgent : public ScActionInitiatedAgent
{
  public:
  ScAddr GetActionClass() const override;

  ScResult DoProgram(ScActionInitiatedEvent const & event, ScAction & action) override;

  ;

private:
  bool checkActionClass(ScAddr const & actionAddr);

  void convertSoatoCodes();

  void sew(const AdministrativeFacility & facility);

  ScAddr initializeFacility(const AdministrativeFacility & facility);

  void addToClassIfNotPresent(ScAddr node, const std::string & className);

  ScAddr createEdgeIfNotPresent(const ScAddr & begin, const ScAddr & end, const ScType & type);
};

}  // namespace soatoClassificationModule
