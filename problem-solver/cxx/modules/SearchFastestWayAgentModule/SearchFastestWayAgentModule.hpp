#pragma once
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "keynodes/keynodes.hpp"
#include "agents/SearchFastestWayAgent.hpp"

namespace SearchFastestWayAgentModule
{

class SearchFastestWayAgentModule : public ScModule
{
  void Initialize(ScMemoryContext* context) override;
  void Shutdown(ScMemoryContext* context) override;
  };
}  // namespace SearchFastestWayAgentModule
