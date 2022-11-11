/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace VitebskVillagesModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:

  SC_PROPERTY(Keynode("question_largerVillageByPopulation"), ForceCreate)
  static ScAddr question_largerVillageByPopulation;

  SC_PROPERTY(Keynode("question_greatestDistanceToTheRegionalCenter"), ForceCreate)
  static ScAddr question_greatestDistanceToTheRegionalCenter;

  SC_PROPERTY(Keynode("nrel_population"), ForceCreate)
  static ScAddr nrel_population;

  SC_PROPERTY(Keynode("nrel_distanceFromArea"), ForceCreate)
  static ScAddr nrel_distanceFromArea;

  SC_PROPERTY(Keynode("nrel_district"), ForceCreate)
  static ScAddr nrel_district;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  
};

} // namespace exampleModule
