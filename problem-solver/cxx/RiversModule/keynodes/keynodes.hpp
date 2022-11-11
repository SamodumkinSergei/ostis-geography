/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace RiversModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("question_theBiggestBasinInRegion"), ForceCreate)
  static ScAddr question_theBiggestBasinInRegion;
  
  SC_PROPERTY(Keynode("question_longerRiver"), ForceCreate)
  static ScAddr question_longerRiver;

  SC_PROPERTY(Keynode("question_shorterRiver"), ForceCreate)
  static ScAddr question_shorterRiver;

  SC_PROPERTY(Keynode("question_biggerBasin"), ForceCreate)
  static ScAddr question_biggerBasin;

  SC_PROPERTY(Keynode("question_longestInRegion"), ForceCreate)
  static ScAddr question_longestInRegion;

  SC_PROPERTY(Keynode("nrel_length"), ForceCreate)
  static ScAddr nrel_length;

  SC_PROPERTY(Keynode("nrel_basin"), ForceCreate)
  static ScAddr nrel_basin;

  SC_PROPERTY(Keynode("nrel_region"), ForceCreate)
  static ScAddr nrel_region;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;
};

} // namespace RiversModule
