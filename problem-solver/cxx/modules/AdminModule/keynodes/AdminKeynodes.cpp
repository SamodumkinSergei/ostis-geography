#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "AdminKeynodes.hpp"

namespace adminModule
{

class AdminKeynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_get_embassy"), ForceCreate)
  static ScAddr action_get_embassy;

  SC_PROPERTY(Keynode("action_get_admin_building_district"), ForceCreate)
  static ScAddr action_get_admin_building_district;

  SC_PROPERTY(Keynode("concept_admin_building"), ForceCreate)
  static ScAddr concept_admin_building;

  SC_PROPERTY(Keynode("action_get_admin_building_region"), ForceCreate)
  static ScAddr action_get_admin_building_region;

  SC_PROPERTY(Keynode("nrel_region"), ForceCreate)
  static ScAddr nrel_region;

  SC_PROPERTY(Keynode("nrel_embassy"), ForceCreate)
  static ScAddr nrel_embassy;

  SC_PROPERTY(Keynode("nrel_search_area"), ForceCreate)
  static ScAddr nrel_search_area;

  SC_PROPERTY(Keynode("minsk"), ForceCreate)
  static ScAddr minsk;
};

} 