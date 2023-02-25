#pragma once
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "keynodes/keynodes.hpp"
#include "agents/SearchFastestWayAgent.hpp"

#include "SearchFastestWayAgentModule.generated.hpp"

namespace SearchFastestWayAgentModule
{

class SearchFastestWayAgentModule : public ScModule
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
}  // namespace SearchFastestWayAgentModule
