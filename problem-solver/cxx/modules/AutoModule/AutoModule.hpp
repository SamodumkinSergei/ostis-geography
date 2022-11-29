/*
* Author Teterski Ivan
*/
#pragma once
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "keynodes/AutoKeynodes.hpp"
#include "agent/FindSiteAgent.hpp"

#include "AutoModule.generated.hpp"

namespace autoModule
{

class AutoModule : public ScModule
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
}