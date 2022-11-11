#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "keynodes/keynodes.hpp"
#include "agents/TheBiggestBasinInRegion.hpp"
#include "agents/LongerRiver.hpp"
#include "agents/LongestInRegion.hpp"
#include "agents/BiggerBasin.hpp"
#include "agents/ShorterRiver.hpp"

#include "RiversModule.generated.hpp"

namespace RiversModule {

class RiversModule : public ScModule
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
}
