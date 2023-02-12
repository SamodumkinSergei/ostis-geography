#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "Keynodes.generated.hpp"

namespace soatoClassificationModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_soato_classification"), ForceCreate)
  static ScAddr action_soato_classification;

  SC_PROPERTY(Keynode("rrel_entity"), ForceCreate)
  static ScAddr rrel_entity;
};

}
