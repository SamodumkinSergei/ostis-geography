#pragma once
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "keynodes/keynodes.hpp"
#include "agents/SearchFastestWayToKhmelnitskogoAgent.hpp"

#include "SearchFastestWayToKhmelnitskogoAgentModule.generated.hpp"

namespace SearchFastestWayToKhmelnitskogoAgentModule
{

class SearchFastestWayToKhmelnitskogoAgentModule : public ScModule
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
}  // namespace SearchFastestWayToKhmelnitskogoAgentModule