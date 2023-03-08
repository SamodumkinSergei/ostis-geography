#pragma once
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "keynodes/keynodes.hpp"
#include "agents/SearchFastestHikingWayAgent.hpp"

#include "SearchFastestHikingWayAgentModule.generated.hpp"

namespace SearchFastestHikingWayAgentModule
{

class SearchFastestHikingWayAgentModule : public ScModule
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
}  // namespace SearchFastestHikingWayAgentModule
