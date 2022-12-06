/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace PotteryModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:



  SC_PROPERTY(Keynode("question_potteryType"), ForceCreate)
  static ScAddr question_potteryType;

  SC_PROPERTY(Keynode("question_potteryTech"), ForceCreate)
  static ScAddr question_potteryTech;

  SC_PROPERTY(Keynode("question_potteryDate"), ForceCreate)
  static ScAddr question_potteryDate;

  SC_PROPERTY(Keynode("nrel_technologies_used"), ForceCreate)
  static ScAddr nrel_technologies_used;

  SC_PROPERTY(Keynode("nrel_type_of_production"), ForceCreate)
  static ScAddr nrel_type_of_production;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  SC_PROPERTY(Keynode("nrel_date"), ForceCreate)
  static ScAddr nrel_date;

  SC_PROPERTY(Keynode("pottery_centre"), ForceCreate)
  static ScAddr pottery_centre;

  //SC_PROPERTY(Keynode("nrel_system_identifier"), ForceCreate)
  //static ScAddr nrel_system_identifier;

  //SC_PROPERTY(Keynode("system_identifier"), ForceCreate)
  //static ScAddr system_identifier;

  //SC_PROPERTY(Keynode("nrel_sys_idtf"), ForceCreate)
  //static ScAddr nrel_sys_idtf;



  
};

} // namespace exampleModule
