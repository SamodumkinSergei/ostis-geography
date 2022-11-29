/*
 * Author Ivan Teterski
 */

#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "AutoKeynodes.generated.hpp"

namespace autoModule
{
class AutoKeynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("nrel_site"), ForceCreate)
  static ScAddr nrel_site;

public:
  SC_PROPERTY(Keynode("action_SiteSearch"), ForceCreate)
  static ScAddr action_SiteSearch;

};
}  // namespace autoModule
